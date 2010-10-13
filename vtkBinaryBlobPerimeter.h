// .NAME vtkPTXReader - read a ptx file
// .SECTION Description
// vtkPTXReader reads a ptx file
// Motivated by http://www.mathworks.com/help/toolbox/images/ref/bwperim.html
#ifndef __vtkBinaryBlobPerimeter_h
#define __vtkBinaryBlobPerimeter_h

#include "vtkImageAlgorithm.h"
#include "vtkSmartPointer.h"

class vtkImageData;

class vtkBinaryBlobPerimeter : public vtkImageAlgorithm
{
public:
  vtkTypeMacro(vtkBinaryBlobPerimeter,vtkImageAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkBinaryBlobPerimeter *New();

  // "Sparse" connectivity is 4-connectedness in 2D, 6-connectedness in 3D
  // "Dense" connectivity is 8-connectedness in 2D, 26-connectedness in 3D
  enum {SPARSECONNECTIVITY, DENSECONNECTIVITY};
protected:
  vtkBinaryBlobPerimeter();
  ~vtkBinaryBlobPerimeter(){}

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:

  vtkBinaryBlobPerimeter(const vtkBinaryBlobPerimeter&);  // Not implemented.
  void operator=(const vtkBinaryBlobPerimeter&);  // Not implemented.
};

#endif
