
#include "dcmtk.h"

Dcmtk::Dcmtk(const std::string& path): IDicomReader(path)   
 ,m_path(path), m_isFileValid(false) {

    m_fileformat = std::make_unique<DcmFileFormat>();
    m_isFileValid = m_fileformat->loadFile(m_path.c_str()).good();
   
    if (m_isFileValid) {
        m_DCMImage = std::make_unique<DicomImage>(m_path.c_str());
    }
}

Dcmtk::~Dcmtk() {
}

std::string Dcmtk::getMetaData() const{
    if (!m_isFileValid) {
        throw std::runtime_error("File is not valid.");
    }
    
    std::ostringstream oss;
    m_fileformat->getDataset()->print(oss);  
    return oss.str();                             
 }

 std::string Dcmtk::getPatientName() const {
    if (!m_isFileValid) {
        throw std::runtime_error("File is not valid.");
    }

    OFString patientName;
    if (m_fileformat->getDataset()->findAndGetOFString(DCM_PatientName, patientName).good())
    {
        return patientName.c_str();
    }
    else{
        return "Error: cannot access Patient's Name!";
    }
 }

long Dcmtk::getImageWidth() const { 
    if (!m_isFileValid) {
        throw std::runtime_error("File is not valid.");
    }

    return m_DCMImage->getWidth();
}

long Dcmtk::getImageHeight() const { 
    if (!m_isFileValid) {
        throw std::runtime_error("File is not valid.");
    }

    return m_DCMImage->getHeight();
}

long Dcmtk::getImageDepth() const{ 
    if (!m_isFileValid) {
        throw std::runtime_error("File is not valid.");
    }

    return m_DCMImage->getDepth();
}

void* Dcmtk::getImageOutputData() const{ 
    if (!m_isFileValid) {
        throw std::runtime_error("File is not valid.");
    }

    return (void*)m_DCMImage->getOutputData(8);
}

 bool Dcmtk::isFileValid() const{
    return  m_isFileValid;
 }

