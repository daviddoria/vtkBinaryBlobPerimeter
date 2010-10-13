cmake_minimum_required(VERSION 2.6)

PROJECT(vtkBinaryBlobPerimeter)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(vtkBinaryBlobPerimeterExample vtkBinaryBlobPerimeterExample.cxx vtkBinaryBlobPerimeter.cxx)
TARGET_LINK_LIBRARIES(vtkBinaryBlobPerimeterExample vtkHybrid )

