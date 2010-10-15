#include "vtkBinaryBlobPerimeter.h"

#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleImage.h>


void FindBoundaryPixels(vtkImageData* input, vtkImageData* boundaryImage);

int main(int, char *[])
{
  vtkSmartPointer<vtkBinaryBlobPerimeter> binaryBlobPerimeter =
    vtkSmartPointer<vtkBinaryBlobPerimeter>::New();

  
  // Create a blank, black image
  vtkSmartPointer<vtkImageCanvasSource2D> source =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetScalarTypeToUnsignedChar();
  source->SetNumberOfScalarComponents(1);
  source->SetExtent(0, 20, 0, 50, 0, 0);
  source->SetDrawColor(0,0,0);
  source->FillBox(0,20,0,50);
  source->SetDrawColor(255, 255, 255);
  source->FillBox(5, 10, 5, 10);
  source->Update();
  
  /*
  // Create a simple image for detailed testing
  vtkSmartPointer<vtkImageCanvasSource2D> source =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetScalarTypeToUnsignedChar();
  source->SetNumberOfScalarComponents(1);
  source->SetExtent(0, 1, 0, 1, 0, 0);
  source->SetDrawColor(0,0,0);
  source->FillBox(0,1,0,1);
  source->SetDrawColor(255, 255, 255);
  source->FillBox(0, 0, 0, 1);
  source->Update();
  */
  
  vtkSmartPointer<vtkBinaryBlobPerimeter> blobPerimeterFilter =
    vtkSmartPointer<vtkBinaryBlobPerimeter>::New();
  blobPerimeterFilter->SetInputConnection(source->GetOutputPort());
  blobPerimeterFilter->Update();
  
  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->SetInput(source->GetOutput());

  vtkSmartPointer<vtkImageActor> perimeterActor =
    vtkSmartPointer<vtkImageActor>::New();
  perimeterActor->SetInput(blobPerimeterFilter->GetOutput());

   // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double perimeterViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> perimeterRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  perimeterRenderer->SetViewport(perimeterViewport);
  perimeterRenderer->AddActor(perimeterActor);
  perimeterRenderer->ResetCamera();
  perimeterRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(perimeterRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  
  return EXIT_SUCCESS;
}


/*
void FindBoundaryPixels(vtkImageData* input, vtkImageData* boundaryImage)
{
  // Find all white pixels that have a black neighbor and store them in boundaryPixels.
  // This function currently assumes we are no where near the border!

  int extent[6];
  input->GetExtent(extent);

  boundaryImage->SetExtent(extent);
  boundaryImage->SetScalarTypeToUnsignedChar();
  boundaryImage->SetNumberOfScalarComponents(1);

  for(int i = extent[0]; i <= extent[1]; i++)
    {
    for(int j = extent[2]; j <= extent[3]; j++)
      {
      unsigned char* maskPixel = static_cast<unsigned char*>(input->GetScalarPointer(i,j,0));
      
      unsigned char* outputPixel = static_cast<unsigned char*>(boundaryImage->GetScalarPointer(i,j,0));
      // Look for white mask pixels with a black neighbor. Mark them as white in the boundaryImage.
      // Mark the rest of the boundary image as black.
      if(maskPixel[0] == 255) // pixel is white
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

        // If we get to here, the pixels is white, but has no black neighbors, so it is not a boundary pixel.
        outputPixel[0] = 0;
        }
      else // If the pixel is not white, it has no chance of being a boundary pixel.
        {
        outputPixel[0] = 0;
        }
        
      }
    }
    
}
*/