/*-----------------------------------------------------------------------------
| Copyright (c) 2013-2017, Nucleic Development Team.
|
| Distributed under the terms of the Modified BSD License.
|
| The full license is in the file COPYING.txt, distributed with this software.
|----------------------------------------------------------------------------*/
#include <cppy/cppy.h>
#include "behaviors.h"
#include "catom.h"
#include "member.h"
#include "memberchange.h"
#include "eventbinder.h"
#include "signalconnector.h"
#include "atomref.h"
#include "atomlist.h"
#include "atomdict.h"
#include "enumtypes.h"
#include "propertyhelper.h"


static PyMethodDef
catom_methods[] = {
    { "reset_property", ( PyCFunction )reset_property, METH_VARARGS,
      "Reset a Property member. For internal use only!" },
    { 0 } // Sentinel
};


static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "catom",
        "catom extension module",
        -1,
        catom_methods,
        NULL,
        NULL,
        NULL,
        NULL
};


PyMODINIT_FUNC PyInit_catom( void )
{
    PyObject *mod = PyModule_Create( &moduledef );
    if( !mod )
        return 0;
    if( import_member() < 0 )
        return 0;
    if( import_memberchange() < 0 )
        return 0;
    if( import_catom() < 0 )
        return 0;
    if( import_eventbinder() < 0 )
        return 0;
    if( import_signalconnector() < 0 )
        return 0;
    if( import_atomref() < 0 )
        return 0;
    if( import_atomlist() < 0 )
        return 0;
    if( import_atomdict() < 0 )
       return 0;
    if( import_enumtypes() < 0 )
        return 0;

    Py_INCREF( &Member_Type );
    Py_INCREF( &CAtom_Type );
    Py_INCREF( &AtomRef_Type );
    Py_INCREF( &AtomList_Type );
    Py_INCREF( &AtomCList_Type );
    Py_INCREF( &AtomDict_Type );
    Py_INCREF( PyGetAttr );
    Py_INCREF( PySetAttr );
    Py_INCREF( PyDelAttr );
    Py_INCREF( PyPostGetAttr );
    Py_INCREF( PyPostSetAttr );
    Py_INCREF( PyDefaultValue );
    Py_INCREF( PyValidate );
    Py_INCREF( PyPostValidate );
    PyModule_AddObject( mod, "Member", pyobject_cast( &Member_Type ) );
    PyModule_AddObject( mod, "CAtom", pyobject_cast( &CAtom_Type ) );
    PyModule_AddObject( mod, "atomref", pyobject_cast( &AtomRef_Type ) );
    PyModule_AddObject( mod, "atomlist", pyobject_cast( &AtomList_Type ) );
    PyModule_AddObject( mod, "atomclist", pyobject_cast( &AtomCList_Type ) );
    PyModule_AddObject( mod, "atomdict", pyobject_cast( &AtomDict_Type ) );
    PyModule_AddObject( mod, "GetAttr", PyGetAttr );
    PyModule_AddObject( mod, "SetAttr", PySetAttr );
    PyModule_AddObject( mod, "DelAttr", PyDelAttr );
    PyModule_AddObject( mod, "PostGetAttr", PyPostGetAttr );
    PyModule_AddObject( mod, "PostSetAttr", PyPostSetAttr );
    PyModule_AddObject( mod, "DefaultValue", PyDefaultValue );
    PyModule_AddObject( mod, "Validate", PyValidate );
    PyModule_AddObject( mod, "PostValidate", PyPostValidate );

    return mod;
}
