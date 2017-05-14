/****************************************************************************
** Meta object code from reading C++ file 'okno.hh'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../data_acquisition/inc/okno.hh"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'okno.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Okno[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      25,    5,    5,    5, 0x0a,
      46,    5,    5,    5, 0x0a,
      63,    5,    5,    5, 0x0a,
      81,    5,    5,    5, 0x0a,
     101,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Okno[] = {
    "Okno\0\0on_start_clicked()\0on_start_m_clicked()\0"
    "SetProgressBar()\0setMeasureIcons()\0"
    "on_accept_clicked()\0on_reject_clicked()\0"
};

void Okno::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Okno *_t = static_cast<Okno *>(_o);
        switch (_id) {
        case 0: _t->on_start_clicked(); break;
        case 1: _t->on_start_m_clicked(); break;
        case 2: _t->SetProgressBar(); break;
        case 3: _t->setMeasureIcons(); break;
        case 4: _t->on_accept_clicked(); break;
        case 5: _t->on_reject_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Okno::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Okno::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Okno,
      qt_meta_data_Okno, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Okno::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Okno::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Okno::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Okno))
        return static_cast<void*>(const_cast< Okno*>(this));
    return QWidget::qt_metacast(_clname);
}

int Okno::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
