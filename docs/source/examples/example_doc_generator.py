#------------------------------------------------------------------------------
# Copyright (c) 2018, Nucleic Development Team.
#
# Distributed under the terms of the Modified BSD License.
#
# The full license is in the file LICENSE, distributed with this software.
#------------------------------------------------------------------------------
""" Generate the Example Documentation for the Atom Examples

Run as part of the documentation build script.

"""
from __future__ import print_function
import os
import re
import sys
from textwrap import dedent


def extract_docstring(script_text):
    """ Extract the docstring from an example Enaml script. """

    # The docstring is found between the first two '"""' strings.
    return script_text.split('"""')[1]


def clean_docstring(docstring):
    """ Convert a docstring into ReStructuredText format. """

    # Find backquoted identifiers, and double the backquotes to match RST.
    docstring = re.sub(
        pattern=r"`(?P<identifier>[A-Za-z_]+)`",  # Backquoted identifiers
        repl=r"``\g<identifier>``",  # Double backquoted identifiers
        string=docstring)

    return docstring.rstrip()


EXAMPLE_DOC_RST_TEMPLATE = dedent("""
    ..
      NOTE: This RST file was generated by `make examples`.
      Do not edit it directly.
      See docs/source/examples/example_doc_generator.py

    {title} Example
    ===============================================================================

    {docstring_rst}

    .. TIP:: To see this example in action, download it from
     :download:`{name} <../../../{path}>`
     and run::

       $ python {name}.py

    Example Atom Code
    -------------------------------------------------------------------------------
    .. literalinclude:: ../../../{path}
        :language: python
    """)


def generate_example_doc(docs_path, script_path):
    """ Generate an RST for an example file.

    Parameters
    ----------
    docs_path : str
         Full path to enaml/docs/source/examples
    script_path : str
         Full path to the example file

    """
    script_name = os.path.basename(script_path)
    script_name = script_name[:script_name.find('.')]
    print('generating doc for %s' % script_name)

    script_title = script_name.replace('_', ' ').title()
    rst_path = os.path.join(
        docs_path, 'ex_' + script_name + '.rst')
    relative_script_path = script_path[
        script_path.find('examples'):].replace('\\', '/')

    # Add the script to the Python Path
    old_python_path = sys.path
    sys.path = sys.path + [os.path.dirname(script_path)]

    # Restore Python path.
    sys.path = old_python_path

    with open(os.path.join(script_path)) as fid:
        script_text = fid.read()

    docstring = clean_docstring(extract_docstring(script_text))

    example_doc_rst = EXAMPLE_DOC_RST_TEMPLATE.format(
        title=script_title,
        name=script_name,
        path=relative_script_path,
        docstring_rst=docstring)

    with open(rst_path, 'wb') as rst_output_file:
        rst_output_file.write(example_doc_rst.lstrip().encode())


def main():
    """ Generate documentation for all atom examples.

    """
    docs_path = os.path.dirname(__file__)
    base_path = '../../../examples'
    base_path = os.path.realpath(os.path.join(docs_path, base_path))

    # Find all the files in the examples directory with a .enaml extension
    # that contain the pragma '<< autodoc-me >>', and generate .rst files for
    # them.
    for dirname, dirnames, filenames in os.walk(base_path):
        files = [os.path.join(dirname, f)
                 for f in filenames if f.endswith('.py')]
        for fname in files:
            generate_example_doc(docs_path, fname)


if __name__ == '__main__':
    main()