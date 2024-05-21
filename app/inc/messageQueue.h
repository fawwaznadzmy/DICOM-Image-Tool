#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>

// Define a structure for the DICOM metadata message
struct MetadataMessage {
    
    std::string metadata;

    bool isValid;

    bool operator==(const MetadataMessage& other) const {
        return metadata == other.metadata && isValid == other.isValid;
    }
};

// Message queue class for passing metadata messages between threads
class MessageQueue {
public:
    // Push a message into the queue
    void push(const MetadataMessage& message) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(message);
        m_condition.notify_one();
    }

    // Pop a message from the queue
    MetadataMessage pop() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock, [this] { return !m_queue.empty(); });
        MetadataMessage message = m_queue.front();
        m_queue.pop();
        return message;
    }

private:
    std::queue<MetadataMessage> m_queue;

    std::mutex m_mutex;

    std::condition_variable m_condition;
};