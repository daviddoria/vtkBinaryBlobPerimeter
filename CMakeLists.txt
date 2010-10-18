cmake_minimum_required(VERSION 2.6)

PROJECT(vtkBinaryBlobPerimeter)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(vtkBinaryBlobPerimeterExample vtkBinaryBlobPerimeter2DExample.cxx vtkBinaryBlobPerimeter2D.cxx)
TARGET_LINK_LIBRARIES(vtkBinaryBlobPerimeterExample vtkHybrid )

