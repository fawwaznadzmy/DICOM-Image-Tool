
#include "dicom.h"

DicomReader::DicomReader(const std::string& path){

    m_DCMImage = new DicomImage(path.c_str());
    m_path = path;
    m_isFileValid = false;

}


std::ostringstream DicomReader::displayMetaData(){
    if(isFileValid()){
        DcmDataset* dataset = m_fileformat.getDataset();
        
        // Print metadata
        //dataset->print(std::cout);
        std::ostringstream oss;
        dataset->print(oss);  
        return oss;                             
    }
 }

 string DicomReader::displayPatientName(){
    OFString patientName;
    if(isFileValid()){
        if (m_fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientName).good())
        {
            return patientName.c_str();
        }
        else
            return "Error: cannot access Patient's Name!";
    }
   
 }

 bool DicomReader::isFileValid(){
    return  m_fileformat.loadFile(m_path.c_str()).good();
 }

void* DicomReader::image(int& width, int& height, int& depth){
     DicomImage DCM_image(m_path.c_str());
     width = DCM_image.getWidth(); 
     height= DCM_image.getHeight(); 
     depth = DCM_image.getDepth();
     return (void*)DCM_image.getOutputData(8);
 }

