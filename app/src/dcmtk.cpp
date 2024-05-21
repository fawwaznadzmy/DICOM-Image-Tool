
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
   
    if (!isFileValid()) {
        throw std::runtime_error("File is not valid.");
    }
    
    std::ostringstream oss;
    m_fileformat->getDataset()->print(oss);  
    return oss.str();                             
 }

 std::string Dcmtk::getPatientName() const {
    if (!isFileValid()) {
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

 bool Dcmtk::isFileValid() const{
    return  m_isFileValid;
 }

