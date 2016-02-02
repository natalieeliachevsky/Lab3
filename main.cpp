#include "QuickView.h"
#include "itkImageFileReader.h"
#include "itkTIFFImageIOFactory.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkThresholdImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkMedianImageFilter.h"
#include <sstream>
#include "itkDiscreteGaussianImageFilter.h"


int main(int, char **)
{
    char inputFile[] = "C:/Users/bmi/Documents/GitHub/Lab3/HR_081507_L_1003.tif";
    unsigned int maximum = 65535;

    typedef itk::Image<unsigned int, 2> ImageType;
    typedef itk::ImageFileReader<ImageType> ReaderType;

    // register TIFF
    itk::TIFFImageIOFactory::RegisterOneFactory();

    ReaderType::Pointer reader = ReaderType::New();


    //read file
    reader->SetFileName(inputFile);
    reader->Update();


    /////////////////////////////////////////
    ///        binary threshold filter
    /////////////////////////////////////////
/*
    typedef itk::BinaryThresholdImageFilter <ImageType, ImageType> BinaryThresholdImageFilterType;
    BinaryThresholdImageFilterType::Pointer thresholdFilter = BinaryThresholdImageFilterType::New();

    unsigned int lowerBinaryThreshold = 42000;
    unsigned int upperBinaryThreshold = maximum;

    thresholdFilter->SetInput(reader->GetOutput());
    thresholdFilter->SetLowerThreshold(lowerBinaryThreshold);
    thresholdFilter->SetUpperThreshold(upperBinaryThreshold);
    thresholdFilter->SetInsideValue(maximum);
    thresholdFilter->SetOutsideValue(0);



    // view the images
    QuickView viewer;
    viewer.AddImage(reader->GetOutput(),
                    true,
                    "Original Image");
    viewer.AddImage(thresholdFilter->GetOutput(),
                    true,
                    "Binary Threshold Filter");
    viewer.Visualize();

*/


    /////////////////////////////////////////
    ///        Threshold Filter
    /////////////////////////////////////////
/*
    typedef itk::ThresholdImageFilter <ImageType> ThresholdImageFilterType;
    ThresholdImageFilterType::Pointer thresholdFilter = ThresholdImageFilterType::New();

    unsigned int lowerThreshold = 42000;
    unsigned int upperThreshold = maximum;

    thresholdFilter->SetInput(reader->GetOutput());
    thresholdFilter->ThresholdOutside(lowerThreshold, upperThreshold);
    thresholdFilter->SetOutsideValue(0);


    // view the images
    QuickView viewer;
    viewer.AddImage(reader->GetOutput(),
                    true,
                    "Original Image");
    viewer.AddImage(thresholdFilter->GetOutput(),
                    true,
                    "Threshold Filter");
    viewer.Visualize();
*/


    /////////////////////////////////////////
    ///        Intensity mapping
    /////////////////////////////////////////

/*
    typedef itk::RescaleIntensityImageFilter< ImageType, ImageType > RescaleFilterType;

    RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();

    rescaleFilter->SetInput(reader->GetOutput());
    rescaleFilter->SetOutputMinimum(0);
    rescaleFilter->SetOutputMaximum(3);

    // view the images
    QuickView viewer;
    viewer.AddImage(reader->GetOutput(),
                    true,
                    "Original Image");
    viewer.AddImage(rescaleFilter->GetOutput(),
                    true,
                    "Intensity Mapping Filter");
    viewer.Visualize();
*/


    /////////////////////////////////////////
    ///        Mean Filter
    /////////////////////////////////////////
/*
    typedef itk::MedianImageFilter<ImageType, ImageType > FilterType;

    FilterType::Pointer medianFilter = FilterType::New();

    FilterType::InputSizeType radius;

    QuickView viewer;
    viewer.AddImage(reader->GetOutput(),
                    true,
                    "Original Image");

    // r = 1;
    radius.Fill( 1.4142f );

    medianFilter->SetRadius(radius);
    medianFilter->SetInput( reader->GetOutput() );
    medianFilter->Update();

    viewer.AddImage(medianFilter->GetOutput(),
                    true,
                    "Median Filter: x=1, y=1, r=1.4142f");

    // r = 2
    radius.Fill( 2.9155f );

    medianFilter->SetRadius(radius);
    medianFilter->SetInput( reader->GetOutput() );
    medianFilter->Update();

    viewer.AddImage(medianFilter->GetOutput(),
                    true,
                     "Median Filter: x=2, y=2, r=2.9155f");

    // r = 3;
    radius.Fill( 4.3012f );

    medianFilter->SetRadius(radius);
    medianFilter->SetInput( reader->GetOutput() );
    medianFilter->Update();

    viewer.AddImage(medianFilter->GetOutput(),
                    true,
                    "Median Filter: x=3, y=3, r=4.3012f");

    // r = 4
    radius.Fill( 5.7009f );

    medianFilter->SetRadius(radius);
    medianFilter->SetInput( reader->GetOutput() );
    medianFilter->Update();

    viewer.AddImage(medianFilter->GetOutput(),
                    true,
                    "Median Filter: x=4, y=4, r=5.7009f");

    //r = 5
    radius.Fill( 7.1063f );

    medianFilter->SetRadius(radius);
    medianFilter->SetInput( reader->GetOutput() );
    medianFilter->Update();

    viewer.AddImage(medianFilter->GetOutput(),
                    true,
                    "Median Filter: x=5, y=5, r=7.1063f");

    // view the images
    viewer.Visualize();
*/


    /////////////////////////////////////////
    ///        Smoothing Filter
    /////////////////////////////////////////

    typedef itk::DiscreteGaussianImageFilter< ImageType, ImageType >  filterType;

    double variance;

    filterType::Pointer gaussianFilter = filterType::New();
    gaussianFilter->SetInput( reader->GetOutput() );


    QuickView viewer;
    viewer.AddImage(reader->GetOutput(),
                    true,
                    "Original Image");


    variance = 2.9;
    gaussianFilter->SetMaximumKernelWidth(14);
    gaussianFilter->SetVariance(variance);
    gaussianFilter->Update();
    viewer.AddImage(gaussianFilter->GetOutput(),
                    true,
                    "Gaussian Filter, variance=2.9, width=14");


    variance = 7.825;
    gaussianFilter->SetMaximumKernelWidth(16);
    gaussianFilter->SetVariance(variance);
    gaussianFilter->Update();
    viewer.AddImage(gaussianFilter->GetOutput(),
                    true,
                    "Gaussian Filter, variance=7.825, width=16");


    variance = 1.1;
    gaussianFilter->SetMaximumKernelWidth(25);
    gaussianFilter->SetVariance(variance);
    gaussianFilter->Update();
    viewer.AddImage(gaussianFilter->GetOutput(),
                    true,
                    "Gaussian Filter, variance=1.1, width=25");


    variance = 22;
    gaussianFilter->SetMaximumKernelWidth(60);
    gaussianFilter->SetVariance(variance);
    gaussianFilter->Update();
    viewer.AddImage(gaussianFilter->GetOutput(),
                    true,
                    "Gaussian Filter, variance=22, width=60");


    variance = 22;
    gaussianFilter->SetMaximumKernelWidth(20);
    gaussianFilter->SetVariance(variance);
    gaussianFilter->Update();
    viewer.AddImage(gaussianFilter->GetOutput(),
                    true,
                    "Gaussian Filter, variance=22, width=20");



    // view the images
    viewer.Visualize();

}
