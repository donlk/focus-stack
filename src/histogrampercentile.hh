// Helper class for calculating percentile points from an image histogram.

#pragma once
#include <opencv2/core.hpp>

namespace focusstack {

class HistogramPercentile
{
public:
  // Construct histogram from image, optionally only the masked pixels.
  // Minimum and maximum value of the image are calculated and the histogram points are divided uniformly.
  HistogramPercentile(const cv::Mat &image, int histogram_size);
  HistogramPercentile(const cv::Mat &image, const cv::Mat &mask, int histogram_size);

  // Fetch calculated minimum and maximum values
  float minimum() const { return m_minimum; }
  float maximum() const { return m_maximum; }

  // Find value below which given ratio of pixels are. Ratio is 0 to 1.
  float percentile(float ratio) const;

private:
  cv::Mat m_histogram;
  float m_minimum;
  float m_maximum;
  int m_total_pixels;
};

}