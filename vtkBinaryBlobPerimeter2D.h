// .NAME vtkPTXReader - read a ptx file
// .SECTION Description
// vtkPTXReader reads a ptx file
// Motivated by http://www.mathworks.com/help/toolbox/images/ref/bwperim.html

#ifndef __vtkBinaryBlobPerimeter2D_h
#define __vtkBinaryBlobPerimeter2D_h

#include "vtkImageAlgorithm.h"
#include "vtkSmartPointer.h"

class vtkImageData;

class vtkBinaryBlobPerimeter2D : public vtkImageAlgorithm
{
public:
  vtkTypeMacro(vtkBinaryBlobPerimeter2D,vtkImageAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkBinaryBlobPerimeter2D *New();

  // "Sparse" connectivity is 4-connectedness in 2D, 6-connectedness in 3D
  // "Dense" connectivity is 8-connectedness in 2D, 26-connectedness in 3D
  enum {SPARSECONNECTIVITY, DENSECONNECTIVITY};
protected:
  vtkBinaryBlobPerimeter2D();
  ~vtkBinaryBlobPerimeter2D(){}

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  int ConnectivityMode;

private:

  vtkBinaryBlobPerimeter2D(const vtkBinaryBlobPerimeter2D&);  // Not implemented.
  void operator=(const vtkBinaryBlobPerimeter2D&);  // Not implemented.
};

#endif
