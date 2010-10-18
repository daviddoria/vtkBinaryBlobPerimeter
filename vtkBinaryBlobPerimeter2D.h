/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkBinaryBlobPerimeter2D.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkBinaryBlobPerimeter2D - finds the boundary of blobs in a binary image
// .SECTION Description
// vtkBinaryBlobPerimeter2D, motivated by the Matlab function bwperim,
// finds the boundary of connected white pixel regions (blobs) in a binary image.
// The ConnectivityMode can be set to SPARSE (4-connectedness) or DENSE
// (8-connectedness)

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
