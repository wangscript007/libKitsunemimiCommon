/**
 *  @file    data_buffer_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef DATA_BUFFER_TEST_H
#define DATA_BUFFER_TEST_H

#include <testing/test.h>

namespace Kitsune
{
namespace Common
{

class DataBuffer_Test
        : public Kitsune::Common::Test
{
public:
    DataBuffer_Test();

private:
    void constructor_test();
    void structSize_test();
    void copyConstructor_test();
    void addData_test();
    void getBlock_test();
    void reset_test();
};

} // namespace Common
} // namespace Kitsune

#endif // DATABUFFER_TEST_H