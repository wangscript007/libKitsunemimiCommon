﻿/**
 *  @file       data_items.cpp
 *
 *  @brief      Data-items for universal data-structures.
 *
 *  @details    These was originally created in libKitsuneJson. Thats why the strint-output of
 *              the structure has still json-format. It can handle list, maps and values and is
 *              used in all of the kitsune-parser libraries as internal data-representation.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/common_items/data_items.h>

namespace Kitsunemimi
{

//===================================================================
// AbstractData
//===================================================================

DataItem::~DataItem() {}

/**
 * @brief request type, of the current data-object
 *
 * @return object-specific entry of the dataTypes-enumeration
 */
DataItem::dataTypes
DataItem::getType() const
{
    return m_type;
}

/**
 * @brief check if DataItem is a DataValue
 */
bool
DataItem::isValue() const
{
    if(m_type == VALUE_TYPE)
    {
        return true;
    }

    return false;
}

/**
 * @brief check if DataItem is a DataMap
 */
bool
DataItem::isMap() const
{
    if(m_type == MAP_TYPE) {
        return true;
    }

    return false;
}

/**
 * @brief check if DataItem is a DataArray
 */
bool
DataItem::isArray() const
{
    if(m_type == ARRAY_TYPE) {
        return true;
    }

    return false;
}

/**
 * @brief check if DataItem is a String-Value
 */
bool
DataItem::isStringValue() const
{
    if(m_valueType == STRING_TYPE) {
        return true;
    }

    return false;
}

/**
 * @brief check if DataItem is a int-Value
 */
bool
DataItem::isIntValue() const
{
    if(m_valueType == INT_TYPE) {
        return true;
    }

    return false;
}

/**
 * @brief check if DataItem is a float-Value
 */
bool
DataItem::isFloatValue() const
{
    if(m_valueType == FLOAT_TYPE) {
        return true;
    }

    return false;
}

/**
 * @brief check if DataItem is a bool-Value
 */
bool
DataItem::isBoolValue() const
{
    if(m_valueType == BOOL_TYPE) {
        return true;
    }

    return false;
}

/**
 * @brief convert to a DataArray
 */
DataArray*
DataItem::toArray()
{
    if(m_type == ARRAY_TYPE) {
        return static_cast<DataArray*>(this);
    }

    return nullptr;
}

/**
 * @brief convert to a DataMap
 */
DataMap*
DataItem::toMap()
{
    if(m_type == MAP_TYPE) {
        return static_cast<DataMap*>(this);
    }

    return nullptr;
}

/**
 * @brief convert to a DataVolue
 */
DataValue*
DataItem::toValue()
{
    if(m_type == VALUE_TYPE)
    {
        return static_cast<DataValue*>(this);
    }

    return nullptr;
}

/**
 * @brief request the string of the data-value, if it is from string-type
 *
 * @return string of the data-value, if data-value is from string-type, else empty string
 */
const std::string
DataItem::getString() const
{
    if(m_valueType == STRING_TYPE)
    {
        const DataValue* value = dynamic_cast<const DataValue*>(this);
        return std::string(value->m_content.stringValue);
    }

    return std::string("");
}

/**
 * @brief request the integer of the data-value, if it is from int-type
 *
 * @return integer of the data-value, if data-value is from int-type, else empty 0
 */
int
DataItem::getInt()
{
    if(m_valueType == INT_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return static_cast<int>(value->m_content.longValue);
    }

    return 0;
}

/**
 * @brief request the flaot of the data-value, if it is from float-type
 *
 * @return float of the data-value, if data-value is from float-type, else empty 0.0
 */
float
DataItem::getFloat()
{
    if(m_valueType == FLOAT_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return static_cast<float>(value->m_content.doubleValue);
    }

    return 0.0f;
}

/**
 * @brief request the integer of the data-value, if it is from int-type
 *
 * @return integer of the data-value, if data-value is from int-type, else empty 0
 */
long
DataItem::getLong()
{
    if(m_valueType == INT_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return value->m_content.longValue;
    }

    return 0l;
}

/**
 * @brief request the flaot of the data-value, if it is from float-type
 *
 * @return float of the data-value, if data-value is from float-type, else empty 0.0
 */
double
DataItem::getDouble()
{
    if(m_valueType == FLOAT_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return value->m_content.doubleValue;
    }

    return 0.0;
}

/**
 * @brief request the bool of the data-value, if it is from bool-type
 *
 * @return bool of the data-value, if data-value is from bool-type, else empty flase
 */
bool
DataItem::getBool()
{
    if(m_valueType == BOOL_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return value->m_content.boolValue;
    }

    return false;
}

/**
 * @brief add indent and linebreak to be better human-readable
 */
void
DataItem::addIndent(std::string* output,
                    const bool indent,
                    const uint32_t level)
{
    if(indent == true)
    {
        output->append("\n");
        for(uint32_t i = 0; i < level; i++) {
            output->append("    ");
        }
    }
}

//===================================================================
// DataValue
//===================================================================

/**
 * @brief DataValue::DataValue
 */
DataValue::DataValue()
{
    m_type = VALUE_TYPE;
    m_valueType = STRING_TYPE;

    m_content.stringValue = new char[1];
    m_content.stringValue[0] = '\0';
}

/**
 * @brief data-value for char-arrays
 */
DataValue::DataValue(const char *text)
{
    m_type = VALUE_TYPE;
    m_valueType = STRING_TYPE;

    const size_t len = strlen(text);

    m_content.stringValue = new char[len+1];
    strncpy(m_content.stringValue, text, len);
    m_content.stringValue[len] = '\0';
}

/**
 * @brief data-value for strings
 */
DataValue::DataValue(const std::string &text)
{
    m_type = VALUE_TYPE;
    m_valueType = STRING_TYPE;

    m_content.stringValue = new char[text.size()+1];
    memcpy(m_content.stringValue, text.c_str(), text.size());
    m_content.stringValue[text.size()] = '\0';
}

/**
 * @brief data-value for integers
 */
DataValue::DataValue(const int value)
{
    m_type = VALUE_TYPE;
    m_valueType = INT_TYPE;
    m_content.longValue = value;
}

/**
 * @brief data-value for float
 */
DataValue::DataValue(const float value)
{
    m_type = VALUE_TYPE;
    m_valueType = FLOAT_TYPE;
    m_content.doubleValue = static_cast<double>(value);
}

/**
 * @brief data-value for long
 */
DataValue::DataValue(const long value)
{
    m_type = VALUE_TYPE;
    m_valueType = INT_TYPE;
    m_content.longValue = value;
}

/**
 * @brief data-value for double
 */
DataValue::DataValue(const double value)
{
    m_type = VALUE_TYPE;
    m_valueType = FLOAT_TYPE;
    m_content.doubleValue = value;
}

/**
 * @brief data-value for bool
 */
DataValue::DataValue(const bool value)
{
    m_type = VALUE_TYPE;
    m_valueType = BOOL_TYPE;
    m_content.boolValue = value;
}

/**
 * @brief copy-assingment-constructor
 */
DataValue::DataValue(const DataValue &other)
{
    clear();

    // copy meta-data
    m_type = other.m_type;
    m_valueType = other.m_valueType;

    // copy content
    if(other.m_valueType == STRING_TYPE)
    {
        const size_t len = strlen(other.m_content.stringValue);

        m_content.stringValue = new char[len+1];
        strncpy(m_content.stringValue, other.m_content.stringValue, len);
        m_content.stringValue[len] = '\0';

        assert(strlen(other.m_content.stringValue) == strlen(m_content.stringValue));
    }
    else
    {
        m_content = other.m_content;
    }
}

/**
 * @brief destructor
 */
DataValue::~DataValue()
{
    clear();
}

/**
 * @brief assignment operator
 */
DataValue
&DataValue::operator=(const DataValue &other)
{
    if(this != &other)
    {
        clear();

        // copy meta-data
        this->m_type = other.m_type;
        this->m_valueType = other.m_valueType;

        // copy content
        if(other.m_valueType == STRING_TYPE)
        {
            const size_t len = strlen(other.m_content.stringValue);

            this->m_content.stringValue = new char[len+1];
            strncpy(this->m_content.stringValue, other.m_content.stringValue, len);
            this->m_content.stringValue[len] = '\0';

            assert(strlen(other.m_content.stringValue) == strlen(this->m_content.stringValue));
        }
        else
        {
            this->m_content = other.m_content;
        }
    }

    return *this;
}

/**
 * @brief get type inside the data-value
 *
 * @return value-type
 */
DataValue::dataValueTypes
DataValue::getValueType()
{
    return m_valueType;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::operator[](const std::string)
{
    return nullptr;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::operator[](const uint64_t)
{
    return nullptr;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::get(const std::string)
{
    return nullptr;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::get(const uint64_t)
{
    return nullptr;
}

/**
 * @brief return size of the values
 *
 * @return length of the string, if string-typed value, else 0
 */
uint64_t
DataValue::size() const
{
    if(m_valueType == STRING_TYPE) {
        return getString().size();
    }
    return 0;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime false
 */
bool
DataValue::remove(const std::string&)
{
    return false;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime false
 */
bool
DataValue::remove(const uint64_t)
{
    return false;
}

/**
 * @brief reset content to int-type with value 0
 */
void
DataValue::clear()
{
    if(m_valueType == STRING_TYPE
            && m_content.stringValue != nullptr)
    {
        delete m_content.stringValue;
    }

    m_type = VALUE_TYPE;
    m_valueType = INT_TYPE;
    m_content.longValue = 0l;
}

/**
 * @brief copy the data-value
 *
 * @return pointer to a copy of the value
 */
DataItem*
DataValue::copy()
{
    DataValue* tempItem = nullptr;

    if(m_valueType == STRING_TYPE) {
        tempItem = new DataValue(std::string(m_content.stringValue));
    }

    if(m_valueType == INT_TYPE) {
        tempItem = new DataValue(m_content.longValue);
    }

    if(m_valueType == FLOAT_TYPE) {
        tempItem = new DataValue(m_content.doubleValue);
    }

    if(m_valueType == BOOL_TYPE) {
        tempItem = new DataValue(m_content.boolValue);
    }

    return tempItem;
}

/**
 * @brief return the content as string
 */
const std::string
DataValue::toString(const bool,
                    std::string* output,
                    const uint32_t)
{
    std::string out = "";
    if(output == nullptr) {
        output = &out;
    }

    if(m_valueType == STRING_TYPE)
    {
        output->append(std::string(m_content.stringValue));
    }

    if(m_valueType == INT_TYPE) {
        output->append(std::to_string(m_content.longValue));
    }

    if(m_valueType == FLOAT_TYPE) {
        output->append(std::to_string(m_content.doubleValue));
    }

    if(m_valueType == BOOL_TYPE)
    {
        if(m_content.boolValue) {
            output->append("true");
        } else {
            output->append("false");
        }
    }

    return out;
}

/**
 * @brief writes a new string into the data-value
 */
void
DataValue::setValue(const char* value)
{
    if(m_valueType == STRING_TYPE) {
        delete m_content.stringValue;
    }

    m_type = VALUE_TYPE;
    m_valueType = STRING_TYPE;

    size_t len = strlen(value);

    m_content.stringValue = new char[len+1];
    strncpy(m_content.stringValue, value, len);
    m_content.stringValue[len] = '\0';
}

/**
 * @brief writes a new string into the data-value
 */
void
DataValue::setValue(const std::string &value)
{
    if(m_valueType == STRING_TYPE) {
        delete m_content.stringValue;
    }

    m_type = VALUE_TYPE;
    m_valueType = STRING_TYPE;

    m_content.stringValue = new char[value.size()+1];
    memcpy(m_content.stringValue, value.c_str(), value.size());
    m_content.stringValue[value.size()] = '\0';
}

/**
 * @brief writes a new integer into the data-value
 */
void
DataValue::setValue(const int &value)
{
    if(m_valueType == STRING_TYPE) {
        delete m_content.stringValue;
    }

    m_type = VALUE_TYPE;
    m_valueType = INT_TYPE;

    m_content.longValue = value;
}

/**
 * @brief writes a new float into the data-value
 */
void
DataValue::setValue(const float &value)
{
    if(m_valueType == STRING_TYPE) {
        delete m_content.stringValue;
    }

    m_type = VALUE_TYPE;
    m_valueType = FLOAT_TYPE;

    m_content.doubleValue = static_cast<double>(value);
}

/**
 * @brief writes a new long integer into the data-value
 */
void
DataValue::setValue(const long &value)
{
    if(m_valueType == STRING_TYPE) {
        delete m_content.stringValue;
    }

    m_type = VALUE_TYPE;
    m_valueType = INT_TYPE;

    m_content.longValue = value;
}

/**
 * @brief writes a new double into the data-value
 */
void
DataValue::setValue(const double &value)
{
    if(m_valueType == STRING_TYPE) {
        delete m_content.stringValue;
    }

    m_type = VALUE_TYPE;
    m_valueType = FLOAT_TYPE;

    m_content.doubleValue = value;
}

/**
 * @brief writes a new boolean into the data-value
 */
void
DataValue::setValue(const bool &value)
{
    if(m_valueType == STRING_TYPE) {
        delete m_content.stringValue;
    }

    m_type = VALUE_TYPE;
    m_valueType = BOOL_TYPE;

    m_content.boolValue = value;
}

//===================================================================
// DataMap
//===================================================================

/**
 * @brief object for key-value-pairs
 */
DataMap::DataMap()
{
    m_type = MAP_TYPE;
}

/**
 * @brief copy-assingment-constructor
 */
DataMap::DataMap(const DataMap &other)
{
    std::map<std::string, DataItem*> otherMap = other.m_map;

    // clear old map
    clear();

    // copy meta-data
    m_type = other.m_type;
    m_valueType = other.m_valueType;

    // copy content
    std::map<std::string, DataItem*>::iterator it;
    for(it = otherMap.begin();
        it != otherMap.end();
        it++)
    {
        if(it->second != nullptr) {
            m_map.insert(std::make_pair(it->first, it->second->copy()));
        } else {
            m_map.insert(std::make_pair(it->first, nullptr));
        }
    }
}

/**
 * @brief delete all items in the key-value-list
 */
DataMap::~DataMap()
{
    clear();
}

/**
 * @brief assignment operator
 */
DataMap
&DataMap::operator=(const DataMap &other)
{
    if(this != &other)
    {
        std::map<std::string, DataItem*> otherMap = other.m_map;

        // clear old map
        clear();

        // copy meta-data
        this->m_type = other.m_type;
        this->m_valueType = other.m_valueType;

        // copy content
        std::map<std::string, DataItem*>::const_iterator it;
        for(it = otherMap.begin();
            it != otherMap.end();
            it++)
        {
            if(it->second != nullptr) {
                this->m_map.insert(make_pair(it->first, it->second->copy()));
            } else {
                this->m_map.insert(std::make_pair(it->first, nullptr));
            }
        }
    }

    return *this;
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index in key is to high, else object
 */
DataItem*
DataMap::operator[](const std::string key)
{
    return get(key);
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index is to high, else object
 */
DataItem*
DataMap::operator[](const uint64_t index)
{
    return get(index);
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index in key is to high, else object
 */
DataItem*
DataMap::get(const std::string key)
{
    std::map<std::string, DataItem*>::const_iterator it;
    it = m_map.find(key);

    if(it != m_map.end()) {
        return it->second;
    }

    return nullptr;
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index is to high, else object
 */
DataItem*
DataMap::get(const uint64_t index)
{
    if(m_map.size() <= index) {
        return nullptr;
    }

    uint32_t counter = 0;
    std::map<std::string, DataItem*>::const_iterator it;
    for(it = m_map.begin();
        it != m_map.end();
        it++)
    {
        if(counter == index) {
            return it->second;
        }
        counter++;
    }

    return nullptr;
}

/**
 * @brief getter for the number of elements in the key-value-list
 *
 * @return number of elements in the key-value-list
 */
uint64_t
DataMap::size() const
{
    return m_map.size();
}

/**
 * @brief get list of keys of the objects-map
 *
 * @return string-list with the keys of the map
 */
const std::vector<std::string>
DataMap::getKeys()
{
    std::vector<std::string> result;
    std::map<std::string, DataItem*>::const_iterator it;
    for(it = m_map.begin();
        it != m_map.end();
        it++)
    {
        result.push_back(it->first);
    }

    return result;
}

/**
 * @brief get list of values of the objects-map
 *
 * @return DataItem-list with the keys of the map
 */
const std::vector<DataItem*>
DataMap::getValues()
{
    std::vector<DataItem*> result;
    std::map<std::string, DataItem*>::const_iterator it;
    for(it = m_map.begin();
        it != m_map.end();
        it++)
    {
        result.push_back(it->second);
    }

    return result;
}

/**
 * @brief check if a key is in the object-map
 *
 * @return false if the key doesn't exist, else true
 */
bool
DataMap::contains(const std::string &key)
{
    std::map<std::string, DataItem*>::const_iterator it;
    it = m_map.find(key);

    if(it != m_map.end())
    {
        return true;
    }

    return false;
}

/**
 * @brief get the string-value behind the key inside the data-map
 */
std::string
DataMap::getStringByKey(const std::string &key)
{
    DataItem* item = get(key);
    if(item == nullptr) {
        return std::string("");
    }

    return item->getString();
}

/**
 * @brief get the int-value behind the key inside the data-map
 */
int
DataMap::getIntByKey(const std::string &key)
{
    DataItem* item = get(key);
    if(item == nullptr) {
        return 0;
    }

    return item->getInt();
}

/**
 * @brief get the float-value behind the key inside the data-map
 */
float
DataMap::getFloatByKey(const std::string &key)
{
    DataItem* item = get(key);
    if(item == nullptr) {
        return 0.0f;
    }

    return item->getFloat();
}

/**
 * @brief get the long-value behind the key inside the data-map
 */
long
DataMap::getLongByKey(const std::string &key)
{
    DataItem* item = get(key);
    if(item == nullptr) {
        return 0l;
    }

    return item->getLong();
}

/**
 * @brief get the double-value behind the key inside the data-map
 */
double
DataMap::getDoubleByKey(const std::string &key)
{
    DataItem* item = get(key);
    if(item == nullptr) {
        return 0.0;
    }

    return item->getDouble();
}

/**
 * @brief remove an item from the key-value-list
 *
 * @return false if the key doesn't exist, else true
 */
bool
DataMap::remove(const std::string &key)
{
    std::map<std::string, DataItem*>::const_iterator it;
    it = m_map.find(key);

    if(it != m_map.end())
    {
        if(it->second != nullptr) {
            delete it->second;
        }
        m_map.erase(it);
        return true;
    }

    return false;
}

/**
 * @brief remove an item from the object
 *
 * @return false if index is to high, else true
 */
bool
DataMap::remove(const uint64_t index)
{
    if(m_map.size() <= index) {
        return false;
    }

    uint32_t counter = 0;
    std::map<std::string, DataItem*>::const_iterator it;
    for(it = m_map.begin();
        it != m_map.end();
        it++)
    {
        if(counter == index)
        {
            if(it->second != nullptr) {
                delete it->second;
            }
            m_map.erase(it);
            return true;
        }
        counter++;
    }

    return false;
}

/**
 * @brief delete all elements from the map
 */
void
DataMap::clear()
{
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_map.begin();
        it != m_map.end();
        it++)
    {
        DataItem* tempItem = it->second;
        if(tempItem != nullptr) {
            delete tempItem;
        }
    }

    m_map.clear();
}

/**
 * @brief copy the object with all elements
 *
 * @return pointer to a copy of the object
 */
DataItem*
DataMap::copy()
{
    DataMap* tempItem = new DataMap();
    std::map<std::string, DataItem*>::const_iterator it;
    for(it = m_map.begin();
        it != m_map.end();
        it++)
    {
        if(it->second == nullptr) {
            tempItem->insert(it->first, nullptr);
        } else {
            tempItem->insert(it->first, it->second->copy());
        }
    }

    return tempItem;
}

/**
 * @brief return the content as string
 */
const std::string
DataMap::toString(const bool indent,
                  std::string* output,
                  const uint32_t level)
{
    std::string out = "";

    if(output == nullptr) {
        output = &out;
    }

    // begin map
    bool firstRun = false;
    output->append("{");

    std::map<std::string, DataItem*>::const_iterator it;
    for(it = m_map.begin();
        it != m_map.end();
        it++)
    {
        if(firstRun) {
            output->append(",");
        }
        firstRun = true;

        // add key
        addIndent(output, indent, level+1);
        output->append("\"");
        output->append(it->first);
        output->append("\"");

        output->append(":");

        if(indent == true) {
            output->append(" ");
        }

        // add value
        if(it->second == nullptr)
        {
            output->append("null");
        }
        else
        {
            // if value is string-item, then set quotes
            if(it->second->isStringValue()) {
                output->append("\"");
            }

            // convert value of item into stirng
            it->second->toString(indent, output, level+1);

            // if value is string-item, then set quotes
            if(it->second->isStringValue()) {
                output->append("\"");
            }
        }
    }

    // close map
    addIndent(output, indent, level);
    output->append("}");

    return out;
}

/**
 * @brief add new key-value-pair to the object
 *
 * @return false if key already exist, else true
 */
bool
DataMap::insert(const std::string &key,
                DataItem* value,
                bool force)
{
    // check if key already exist
    std::map<std::string, DataItem*>::iterator it;
    it = m_map.find(key);
    if(it != m_map.end()
            && force == false)
    {
        return false;
    }

    // if already exist and should be overwritten,
    // then delete the old one at first and insert the new one
    if(it != m_map.end())
    {
        if(it->second != nullptr) {
            delete it->second;
        }
        it->second = value;
    }
    else
    {
        m_map.insert(std::make_pair(key, value));
    }

    return true;
}

//===================================================================
// DataArray
//===================================================================

/**
 * @brief array for items in data-style
 */
DataArray::DataArray()
{
    m_type = ARRAY_TYPE;
}

/**
 * @brief copy-assingment-constructor
 */
DataArray::DataArray(const DataArray &other)
{
    // clear old array
    clear();

    // copy meta-data
    m_type = other.m_type;
    m_valueType = other.m_valueType;

    // copy content
    for(uint32_t i = 0; i < other.m_array.size(); i++)
    {
        if(other.m_array[i] != nullptr) {
            m_array.push_back(other.m_array[i]->copy());
        } else {
            m_array.push_back(nullptr);
        }
    }
}

/**
 * @brief delete all items in the array
 */
DataArray::~DataArray()
{
    clear();
}

/**
 * @brief copy-assignment operator
 */
DataArray
&DataArray::operator=(const DataArray &other)
{
    if(this != &other)
    {
        // clear old array
        clear();

        // copy meta-data
        this->m_type = other.m_type;
        this->m_valueType = other.m_valueType;

        // copy content
        for(uint32_t i = 0; i < other.m_array.size(); i++)
        {
            if(other.m_array[i] != nullptr) {
                this->m_array.push_back(other.m_array[i]->copy());
            } else {
                this->m_array.push_back(nullptr);
            }
        }
    }

    return *this;
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index in key is to high, else true
 */
DataItem*
DataArray::operator[](const std::string key)
{
    return get(key);
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index is to high, else true
 */
DataItem*
DataArray::operator[](const uint64_t index)
{
    return get(index);
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index in key is to high, else object
 */
DataItem*
DataArray::get(const std::string)
{
    return nullptr;
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index is to high, else the object
 */
DataItem*
DataArray::get(const uint64_t index)
{
    if(m_array.size() <= index) {
        return nullptr;
    }

    return m_array[index];
}

/**
 * @brief getter for the number of elements in the array
 *
 * @return number of elements in the array
 */
uint64_t
DataArray::size() const
{
    return m_array.size();
}

/**
 * @brief remove an item from the array
 *
 * @return false if index in key is to high, else true
 */
bool
DataArray::remove(const std::string &key)
{
    const uint32_t index = static_cast<uint32_t>(std::stoi(key));

    if(m_array.size() <= index) {
        return false;
    }

    DataItem* tempItem = m_array[index];
    if(tempItem != nullptr) {
        delete tempItem;
    }

    m_array.erase(m_array.begin() + index);

    return true;
}

/**
 * @brief remove an item from the array
 *
 * @return false if index is to high, else true
 */
bool
DataArray::remove(const uint64_t index)
{
    if(m_array.size() <= index) {
        return false;
    }

    DataItem* tempItem = m_array[index];
    if(tempItem != nullptr) {
        delete tempItem;
    }

    m_array.erase(m_array.begin() + static_cast<uint32_t>(index));

    return true;
}

/**
 * @brief delete all elements from the array
 */
void
DataArray::clear()
{
    for(uint32_t i = 0; i < this->m_array.size(); i++)
    {
        DataItem* tempItem = this->m_array[i];
        if(tempItem != nullptr) {
            delete tempItem;
        }
    }

    this->m_array.clear();
}

/**
 * @brief copy the array with all elements
 *
 * @return pointer to a copy of the array
 */
DataItem*
DataArray::copy()
{
    DataArray* tempItem = new DataArray();

    for(uint32_t i = 0; i < m_array.size(); i++)
    {
        if(m_array[i] == nullptr) {
            tempItem->append(nullptr);
        } else {
            tempItem->append(m_array[i]->copy());
        }
    }

    return tempItem;
}

/**
 * @brief return the content as string
 */
const std::string
DataArray::toString(const bool indent,
                    std::string* output,
                    const uint32_t level)
{
    std::string out = "";

    if(output == nullptr) {
        output = &out;
    }

    // begin array
    output->append("[");
    addIndent(output, indent, level+1);

    std::vector<DataItem*>::const_iterator it;
    for(it = m_array.begin(); it != m_array.end(); it++)
    {
        // separate items of the array with comma
        if(it != m_array.begin())
        {
            output->append(",");
            addIndent(output, indent, level+1);
        }

        // add value
        if((*it) == nullptr)
        {
            output->append("null");
        }
        else
        {
            // if value is string-item, then set quotes
            if((*it)->isStringValue()) {
                output->append("\"");
            }

            // convert value of item into stirng
            (*it)->toString(indent, output, level+1);

            // if value is string-item, then set quotes
            if((*it)->isStringValue()) {
                output->append("\"");
            }
        }
    }

    // close array
    addIndent(output, indent, level);
    output->append("]");

    return out;
}

/**
 * @brief add a new item to the array
 */
void
DataArray::append(DataItem* item)
{
    m_array.push_back(item);
}

}  // namespace Kitsunemimi
