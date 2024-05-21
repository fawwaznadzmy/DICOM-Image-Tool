#include "gtest/gtest.h"
#include "messageQueue.h"

// Test fixture for MessageQueue tests
class MessageQueueTest : public ::testing::Test {
protected:
    MessageQueue messageQueue;
};

// Test pushing and popping a single message
TEST_F(MessageQueueTest, PushPopSingleMessage) {
    MetadataMessage message = {"Test metadata", true};
    messageQueue.push(message);
    MetadataMessage poppedMessage = messageQueue.pop();
    EXPECT_EQ(message, poppedMessage);
}

// Test popping a message from an empty queue (blocking call)
TEST_F(MessageQueueTest, PopFromEmptyQueue) {
    std::thread producer([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        MetadataMessage message{"Delayed metadata", true};
        messageQueue.push(message);
    });

    MetadataMessage poppedMessage = messageQueue.pop();
    EXPECT_EQ(poppedMessage.metadata, "Delayed metadata");
    EXPECT_TRUE(poppedMessage.isValid);

    producer.join();
}

// Test multiple messages
TEST_F(MessageQueueTest, MultipleMessages) {
    MetadataMessage message1{"Metadata 1", true};
    MetadataMessage message2{"Metadata 2", false};
    MetadataMessage message3{"Metadata 3", true};

    messageQueue.push(message1);
    messageQueue.push(message2);
    messageQueue.push(message3);

    EXPECT_EQ(messageQueue.pop(), message1);
    EXPECT_EQ(messageQueue.pop(), message2);
    EXPECT_EQ(messageQueue.pop(), message3);
}

