#include "vtkBinaryBlobPerimeter.h"

#include <vtkSmartPointer.h>
#include <vtkImageData.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkBinaryBlobPerimeter> binaryBlobPerimeter =
    vtkSmartPointer<vtkBinaryBlobPerimeter>::New();


  return EXIT_SUCCESS;
}
