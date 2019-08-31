﻿/**
 *  @file    data_items_DataValue_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "data_items_DataValue_test.h"
#include <common_items/data_items.h>

namespace Kitsune
{
namespace Common
{

DataItems_DataValue_Test::DataItems_DataValue_Test()
    : Kitsune::Common::UnitTest("DataItems_DataValue_Test")
{
    operator_test();
    get_test();
    getSize_test();
    remove_test();
    copy_test();
    toString_test();
    getType_test();
    isValue_isMap_isArray_test();
    toValue_toMap_toArray_test();
    getString_getInt_getFloat_test();

    // value-exclusive
    getValueType_test();
    setValue_test();
}

/**
 * operator_test
 */
void
DataItems_DataValue_Test::operator_test()
{
    DataValue defaultValue;

    // int-access
    bool isNullptr = defaultValue[1] == nullptr;
    UNITTEST(isNullptr, true);

    // string-access
    isNullptr = defaultValue["1"] == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * get_test
 */
void
DataItems_DataValue_Test::get_test()
{
    DataValue defaultValue;

    // int-access
    bool isNullptr = defaultValue.get(1) == nullptr;
    UNITTEST(isNullptr, true);

    // string-access
    isNullptr = defaultValue.get("1") == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * getSize_test
 */
void
DataItems_DataValue_Test::getSize_test()
{
    DataValue defaultValue;
    UNITTEST(defaultValue.size(), 0);
}

/**
 * remove_test
 */
void
DataItems_DataValue_Test::remove_test()
{
    DataValue defaultValue;
    UNITTEST(defaultValue.remove(1), false);
}

/**
 * copy_test
 */
void
DataItems_DataValue_Test::copy_test()
{
    // init
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    // default-value
    DataValue* defaultValueCopy = dynamic_cast<DataValue*>(defaultValue.copy());
    UNITTEST(defaultValue.m_stringValue, defaultValueCopy->m_stringValue);

    // string-value
    DataValue* stringValueCopy = dynamic_cast<DataValue*>(stringValue.copy());
    UNITTEST(stringValue.m_stringValue, stringValueCopy->m_stringValue);

    // int-value
    DataValue* intValueCopy = dynamic_cast<DataValue*>(intValue.copy());
    UNITTEST(intValue.m_intValue, intValueCopy->m_intValue);

    // float-value
    DataValue* floatValueCopy = dynamic_cast<DataValue*>(floatValue.copy());
    UNITTEST(floatValue.m_floatValue, floatValueCopy->m_floatValue);

    // cleanup
    delete defaultValueCopy;
    delete stringValueCopy;
    delete intValueCopy;
    delete floatValueCopy;
}

/**
 * toString_test
 */
void
DataItems_DataValue_Test::toString_test()
{
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    UNITTEST(defaultValue.toString(), "\"\"");
    UNITTEST(stringValue.toString(), "\"test\"");
    UNITTEST(intValue.toString(), "42");
    UNITTEST(floatValue.toString(), "42.500000");
}

/**
 * getType_test
 */
void
DataItems_DataValue_Test::getType_test()
{
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    UNITTEST(defaultValue.getType(), DataItem::VALUE_TYPE);
    UNITTEST(stringValue.getType(), DataItem::VALUE_TYPE);
    UNITTEST(intValue.getType(), DataItem::VALUE_TYPE);
    UNITTEST(floatValue.getType(), DataItem::VALUE_TYPE);
}

/**
 * isValue_isMap_isArray_test
 */
void
DataItems_DataValue_Test::isValue_isMap_isArray_test()
{
    DataValue defaultValue;
    UNITTEST(defaultValue.isValue(), true);
    UNITTEST(defaultValue.isMap(), false);
    UNITTEST(defaultValue.isArray(), false);
}

/**
 * toValue_toMap_toArray_test
 */
void
DataItems_DataValue_Test::toValue_toMap_toArray_test()
{
    DataValue defaultValue;

    bool isNullptr = defaultValue.toMap() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = defaultValue.toArray() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = defaultValue.toValue() == nullptr;
    UNITTEST(isNullptr, false);
}

/**
 * getString_getInt_getFloat_test
 */
void
DataItems_DataValue_Test::getString_getInt_getFloat_test()
{
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    // default-value
    UNITTEST(defaultValue.getString(), "");
    UNITTEST(defaultValue.getInt(), 0);
    UNITTEST(defaultValue.getFloat(), 0.0f);

    // string-value
    UNITTEST(stringValue.getString(), "test");
    UNITTEST(stringValue.getInt(), 0);
    UNITTEST(stringValue.getFloat(), 0.0f);

    // int-value
    UNITTEST(intValue.getString(), "42");
    UNITTEST(intValue.getInt(), 42);
    UNITTEST(intValue.getFloat(), 0.0f);

    // float-value
    UNITTEST(floatValue.getString(), "42.500000");
    UNITTEST(floatValue.getInt(), 0);
    UNITTEST(floatValue.getFloat(), 42.5f);
}

/**
 * getValueType_test
 */
void
DataItems_DataValue_Test::getValueType_test()
{
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    UNITTEST(defaultValue.getValueType(), DataItem::STRING_TYPE);
    UNITTEST(stringValue.getValueType(), DataItem::STRING_TYPE);
    UNITTEST(intValue.getValueType(), DataItem::INT_TYPE);
    UNITTEST(floatValue.getValueType(), DataItem::FLOAT_TYPE);
}

/**
 * setValue_test
 */
void
DataItems_DataValue_Test::setValue_test()
{
    DataValue defaultValue;

    // string-value
    defaultValue.setValue("test");
    UNITTEST(defaultValue.getValueType(), DataItem::STRING_TYPE);
    UNITTEST(defaultValue.m_stringValue, "test");
    UNITTEST(defaultValue.m_intValue, 0);
    UNITTEST(defaultValue.m_floatValue, 0.0f);

    // int-value
    defaultValue.setValue(42);
    UNITTEST(defaultValue.getValueType(), DataItem::INT_TYPE);
    UNITTEST(defaultValue.m_stringValue, "");
    UNITTEST(defaultValue.m_intValue, 42);
    UNITTEST(defaultValue.m_floatValue, 0.0f);

    // float-value
    defaultValue.setValue(42.5f);
    UNITTEST(defaultValue.getValueType(), DataItem::FLOAT_TYPE);
    UNITTEST(defaultValue.m_stringValue, "");
    UNITTEST(defaultValue.m_intValue, 0);
    UNITTEST(defaultValue.m_floatValue, 42.5f);
}

}  // namespace Common
}  // namespace Kitsune
