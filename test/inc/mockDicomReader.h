#pragma once
#include <iostream>
#include "gmock/gmock.h"
#include "dicomInterface.h"

class MockDicomReader : public IDicomReader {
public:
    // Constructor
    MockDicomReader(const std::string& path) : IDicomReader(path) {}

    MOCK_CONST_METHOD0(isFileValid, bool());
    MOCK_CONST_METHOD0(getMetaData, std::string());
    MOCK_CONST_METHOD0(getPatientName, std::string());
    MOCK_CONST_METHOD0(getImageWidth, long());
    MOCK_CONST_METHOD0(getImageHeight, long());
    MOCK_CONST_METHOD0(getImageDepth, long());
    MOCK_CONST_METHOD0(getImageOutputData, void*());

};

