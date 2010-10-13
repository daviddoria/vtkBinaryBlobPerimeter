#include "vtkBinaryBlobPerimeter.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkImageData.h"
#include "vtkSmartPointer.h"

vtkStandardNewMacro(vtkBinaryBlobPerimeter);

vtkBinaryBlobPerimeter::vtkBinaryBlobPerimeter()
{

}

int vtkBinaryBlobPerimeter::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{

  // Get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  // Get the input
  vtkImageData *input = vtkImageData::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));

  if(input->GetScalarType() != VTK_INT)
    {
    vtkErrorMacro(<< "Input scalar type must be int!");
    }

  // Get the ouptut
  vtkImageData *output = vtkImageData::SafeDownCast(
          outInfo->Get(vtkDataObject::DATA_OBJECT()));

  int extent[6];
  input->GetExtent(extent);
  for(int z = extent[4]; z < extent[5]; z++)
    {
    for(int y = extent[2]; y < extent[3]; y++)
      {
      for(int x = extent[0]; x < extent[1]; x++)
        {
        int* pixel = static_cast<int*>(input->GetScalarPointer(x,y,z));
        pixel[0] = 2.0;
        }
      }
    }
  output->SetWholeExtent(output->GetExtent());
  return 1;
}


//----------------------------------------------------------------------------
void vtkBinaryBlobPerimeter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

