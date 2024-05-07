
#include "dicom.h"

DicomReader::DicomReader(const std::string& path)   
 : m_path(path), m_isFileValid(false) {
    
    m_isFileValid = m_fileformat.loadFile(m_path.c_str()).good();
   
    if (m_isFileValid) {
        m_DCMImage = std::make_unique<DicomImage>(m_path.c_str());
    }
}

DicomReader::~DicomReader() {
    // No need to explicitly delete m_DCMImage, it's automatically managed by std::unique_ptr.
}

std::string DicomReader::displayMetaData(){
   
    if (!isFileValid()) {
        throw std::runtime_error("File is not valid.");
    }
    
    std::ostringstream oss;
    m_fileformat.getDataset()->print(oss);  
    return oss.str();                             
 }

 std::string DicomReader::displayPatientName(){
    if (!isFileValid()) {
        throw std::runtime_error("File is not valid.");
    }

    OFString patientName;
    if (m_fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientName).good())
    {
        return patientName.c_str();
    }
    else{
        return "Error: cannot access Patient's Name!";
    }
 }

 bool DicomReader::isFileValid(){
    return  m_isFileValid;
 }

void* DicomReader::getImageData(int& width, int& height, int& depth){
    if (!isFileValid()) {
        throw std::runtime_error("File is not valid.");
    }

    width = m_DCMImage->getWidth();
    height = m_DCMImage->getHeight();
    depth = m_DCMImage->getDepth();
    return (void*)m_DCMImage->getOutputData(8);
 }

