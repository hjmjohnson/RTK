/*=========================================================================
 *
 *  Copyright RTK Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef __rtkAmsterdamShroudImageFilter_h
#define __rtkAmsterdamShroudImageFilter_h

#include <itkImageToImageFilter.h>
#include <itkRecursiveGaussianImageFilter.h>
#include <itkMultiplyByConstantImageFilter.h>
#include <itkThresholdImageFilter.h>
#include <itkSumProjectionImageFilter.h>
#include <itkConvolutionImageFilter.h>
#include <itkSubtractImageFilter.h>
#include <itkPermuteAxesImageFilter.h>

/** \class AmsterdamShroudImageFilter
 * \brief TODO
 *
 * TODO
 *
 * \author Simon Rit
 */
namespace rtk
{

template<class TInputImage, class TOutputImage=
           itk::Image<typename TInputImage::PixelType, TInputImage::ImageDimension-1> >
class ITK_EXPORT AmsterdamShroudImageFilter :
  public itk::ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard class typedefs. */
  typedef AmsterdamShroudImageFilter                         Self;
  typedef itk::ImageToImageFilter<TInputImage, TOutputImage> Superclass;
  typedef itk::SmartPointer<Self>                            Pointer;
  typedef itk::SmartPointer<const Self>                      ConstPointer;

  /** ImageDimension constants */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension);
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      TOutputImage::ImageDimension);
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TOutputImage::ImageDimension);

  /** Standard New method. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(AmsterdamShroudImageFilter, itk::ImageToImageFilter);
protected:
  AmsterdamShroudImageFilter();
  ~AmsterdamShroudImageFilter(){}

  void GenerateOutputInformation();
  void GenerateInputRequestedRegion();

  /** Single-threaded version of GenerateData.  This filter delegates
   * to other filters. */
  void GenerateData();

private:
  AmsterdamShroudImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&);             //purposely not implemented

  typedef itk::RecursiveGaussianImageFilter< TInputImage, TInputImage >          DerivativeType;
  typedef itk::MultiplyByConstantImageFilter< TInputImage, double, TInputImage > NegativeType;
  typedef itk::ThresholdImageFilter< TInputImage >                               ThresholdType;
  typedef itk::SumProjectionImageFilter< TInputImage, TOutputImage >             SumType;
  typedef itk::ConvolutionImageFilter< TOutputImage, TOutputImage >              ConvolutionType;
  typedef itk::SubtractImageFilter< TOutputImage, TOutputImage >                 SubtractType;
  typedef itk::PermuteAxesImageFilter< TOutputImage >                            PermuteType;

  typename DerivativeType::Pointer m_DerivativeFilter;
  typename NegativeType::Pointer m_NegativeFilter;
  typename ThresholdType::Pointer m_ThresholdFilter;
  typename SumType::Pointer m_SumFilter;
  typename ConvolutionType::Pointer m_ConvolutionFilter;
  typename SubtractType::Pointer m_SubtractFilter;
  typename PermuteType::Pointer m_PermuteFilter;
}; // end of class

} // end namespace rtk

#ifndef ITK_MANUAL_INSTANTIATION
#include "rtkAmsterdamShroudImageFilter.txx"
#endif

#endif