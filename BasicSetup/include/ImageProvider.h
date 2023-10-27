#pragma once

#include <QImage>
#include <QQuickImageProvider>

namespace
{
    //-----------------------------------
    void convertToGraScale(QImage& image)
    {
        QSize size = image.size();
        int row = size.width();
        int col = size.height();

        for(int x = 0; x < row; ++x)
        {
            for(int y = 0; y < col; ++y)
            {
                QColor rgb = image.pixelColor(x,y);

                int intensity_pixel = (rgb.red() + rgb.blue() + rgb.green())/3;

                QColor new_color(intensity_pixel,intensity_pixel,intensity_pixel);

                image.setPixelColor(x,y,new_color);
            }
        }
    }

    //-----------------------------------
    //Expects a grayscale image
    void convertToBinary(QImage& image, int threshold = 128, int upperLimit = 255)
    {
        if(!image.isGrayscale())
        {
            convertToGraScale(image);
        }

        QSize size = image.size();
        int row = size.width();
        int col = size.height();

        for(int x = 0; x < row; ++x)
        {
            for(int y = 0; y < col; ++y)
            {
                QColor rgb = image.pixelColor(x,y);
                //R,G and B are all the same for each pixel for a grayscale image
                //so we will only take one for our calculation
                int new_intensity = 0;
                if(rgb.red() > threshold)
                {
                    new_intensity = upperLimit;
                }

                QColor new_color(new_intensity,new_intensity,new_intensity);
                image.setPixelColor(x,y,new_color);
            }
        }
    }

    //-----------------------------------
    void invertBinary(QImage& image, int threshold = 128, int upperLimit = 255)
    {
        if(!image.isGrayscale())
        {
            convertToGraScale(image);
        }

        convertToBinary(image, threshold, upperLimit);

        QSize size = image.size();
        int row = size.width();
        int col = size.height();

        for(int x = 0; x < row; ++x)
        {
            for(int y = 0; y < col; ++y)
            {
                QColor rgb = image.pixelColor(x,y);
                //basically invert white with black and vice-versa
                int new_intensity = upperLimit;
                if(rgb.red() == upperLimit)
                {
                    new_intensity = 0;
                }

                QColor new_color(new_intensity,new_intensity,new_intensity);
                image.setPixelColor(x,y,new_color);
            }
        }
    }
}

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider()
        : QQuickImageProvider(QQmlImageProviderBase::Image)
    {
    }

    ~ImageProvider() override = default;
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override
    {
        //change to desired image path.
        m_image = QImage("/Users/Hilton/Desktop/Images/cat1.jpg");
        convertToGraScale(m_image);
        return m_image;
    }

private:
    QImage m_image;
};
