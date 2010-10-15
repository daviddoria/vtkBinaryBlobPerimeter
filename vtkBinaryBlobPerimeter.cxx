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
  this->ConnectivityMode = SPARSECONNECTIVITY;
}

int vtkBinaryBlobPerimeter::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{
  // Find all white pixels that have a black neighbor and store them in boundaryPixels.
  // This function currently assumes we are no where near the border!
  
  // Get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  // Get the input
  vtkImageData *input = vtkImageData::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));

  if(input->GetScalarType() != VTK_UNSIGNED_CHAR)
    {
    vtkErrorMacro(<< "Input scalar type must be unsigned char!");
    }
  if(input->GetNumberOfScalarComponents() != 1)
    {
    vtkErrorMacro(<< "Input must have 1 scalar!");
    }

  // Get the ouptut
  vtkImageData *output = vtkImageData::SafeDownCast(
          outInfo->Get(vtkDataObject::DATA_OBJECT()));

  output->DeepCopy(input);
  
  int extent[6];
  input->GetExtent(extent);
  unsigned int counter = 0;
  for(int k = extent[4]; k <= extent[5]; k++)
    {
    for(int j = extent[2]; j <= extent[3]; j++)
      {
      for(int i = extent[0]; i <= extent[1]; i++)
        {
        counter++;
        unsigned char* pixel = static_cast<unsigned char*>(input->GetScalarPointer(i,j,k));
        //std::cout << "pixel = " << (int)pixel[0] << std::endl;
      
        unsigned char* outputPixel = static_cast<unsigned char*>(output->GetScalarPointer(i,j,k));
        // Look for white mask pixels with a black neighbor. Mark them as white in the boundaryImage.
        // Mark the rest of the boundary image as black.
        if(pixel[0] == 255) // pixel is white
          {
          unsigned char* top = static_cast<unsigned char*>(input->GetScalarPointer(i,j-1,0));
          if(top[0] == 0)
            {
            outputPixel[0] = 255;
            continue;
            }
          unsigned char* bottom = static_cast<unsigned char*>(input->GetScalarPointer(i,j+1,0));
          if(bottom[0] == 0)
            {
            outputPixel[0] = 255;
            continue;
            }
          unsigned char* left = static_cast<unsigned char*>(input->GetScalarPointer(i-1,j,0));
          if(left[0] == 0)
            {
            outputPixel[0] = 255;
            continue;
            }
          unsigned char* right = static_cast<unsigned char*>(input->GetScalarPointer(i+1,j,0));
          if(right[0] == 0)
            {
            outputPixel[0] = 255;
            continue;
            }

          if(this->ConnectivityMode == DENSECONNECTIVITY)
            {
            unsigned char* topRight = static_cast<unsigned char*>(input->GetScalarPointer(i+1,j-1,0));
            if(topRight[0] == 0)
              {
              outputPixel[0] = 255;
              continue;
              }
            unsigned char* bottomRight = static_cast<unsigned char*>(input->GetScalarPointer(i+1,j+1,0));
            if(bottomRight[0] == 0)
              {
              outputPixel[0] = 255;
              continue;
              }
            unsigned char* topLeft = static_cast<unsigned char*>(input->GetScalarPointer(i-1,j-1,0));
            if(topLeft[0] == 0)
              {
              outputPixel[0] = 255;
              continue;
              }
            unsigned char* bottomLeft = static_cast<unsigned char*>(input->GetScalarPointer(i-1,j+1,0));
            if(bottomLeft[0] == 0)
              {
              outputPixel[0] = 255;
              continue;
              }
            }

          // If we get to here, the pixels is white, but has no black neighbors, so it is not a boundary pixel.
          outputPixel[0] = 0;
          counter--;
          }
        else // If the pixel is not white, it has no chance of being a boundary pixel.
          {
          outputPixel[0] = 0;
          counter--;
          }
        
        }
      }
    }

  std::cout << counter << " Pixels marked as boundary pixels" << std::endl;
    
  output->SetExtent(input->GetExtent());
  output->SetUpdateExtent(output->GetExtent());
  output->SetWholeExtent(output->GetExtent());

  return 1;
}


//----------------------------------------------------------------------------
void vtkBinaryBlobPerimeter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

