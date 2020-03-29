#ifndef BLOCK_BUFFER_RESERVE_TEST_H
#define BLOCK_BUFFER_RESERVE_TEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{

class StackBufferReserve_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    StackBufferReserve_Test();

private:
    void addBuffer_test();
    void getNumberOfBuffers_test();
    void getBuffer_test();
};

} // namespace Kitsunemimi

#endif // BLOCK_BUFFER_RESERVE_TEST_H