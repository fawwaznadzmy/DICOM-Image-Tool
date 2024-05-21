#pragma once

#include "myImage.h"
#include <mutex>
#include <queue>
#include <condition_variable>
#include <fstream>
#include <cstdlib>

// Define a structure for the DICOM metadata message
struct MetadataMessage {
    std::string metadata;
    bool isValid;
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

void displayMetadata(MessageQueue& messageQueue);

class MyThread{
public:
    MyThread(const std::string& path);
    void worker(MessageQueue& messageQueue);
private:
    std::unique_ptr<MyImage> image;
    std::string m_path;
    MetadataMessage m_message;
};




