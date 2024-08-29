# Load the ggplot2 package
library(ggplot2)

# Data organized in a dataframe with Compression Ratios
data <- data.frame(
  Original_Size_GiB = c(5.00, 5.00, 5.00, 5.00, 4.00, 4.00, 4.00, 4.00, 3.00, 3.00, 3.00, 3.00, 2.00, 2.00, 2.00, 2.00, 1.00, 1.00, 1.00, 1.00, 0.512, 0.512, 0.512, 0.512, 0.256, 0.256, 0.256, 0.256),
  Compressed_Size_GiB = c(5.00, 5.02, 5.00, 5.00, 4.00, 4.02, 4.00, 4.00, 3.00, 3.01, 3.00, 3.00, 2.00, 2.01, 2.00, 2.00, 1.00, 1.00, 1.00, 1.00, 0.512, 0.514, 0.512, 0.512, 0.256, 0.257, 0.256, 0.256),
  Time_s = c(4, 438, 137, 7, 3, 352, 110, 6, 2, 264, 82, 5, 1, 176, 55, 2, 0, 88, 27, 1, 0, 44, 13, 0, 0, 21, 6, 0),
  Algorithm = rep(c("zstd", "bzip2", "gzip", "lz4"), 7)
)

# Calculate Compression Ratio
data$Compression_Ratio = data$Original_Size_GiB / data$Compressed_Size_GiB

# Common theme to increase text size
custom_theme <- theme(
  plot.title = element_text(size = 20, face = "bold"),
  axis.title.x = element_text(size = 16),
  axis.title.y = element_text(size = 16),
  axis.text = element_text(size = 14),
  legend.title = element_text(size = 16),
  legend.text = element_text(size = 14)
)

# Plot 1: Dimension vs Time
ggplot(data, aes(x = Original_Size_GiB, y = Time_s, color = Algorithm)) +
  geom_line(size = 1) +
  geom_point(size = 3) +
  labs(title = "Dimension vs Time", x = "Dimension (GiB)", y = "Time (s)") +
  custom_theme

# Plot 2: Dimension vs Speed
ggplot(data, aes(x = Original_Size_GiB, y = Original_Size_GiB / Time_s, color = Algorithm)) +
  geom_line(size = 1) +
  geom_point(size = 3) +
  labs(title = "Dimension vs Speed", x = "Dimension (GiB)", y = "Speed (GiB/s)") +
  custom_theme

# Plot 3: Compression Ratio vs Time
ggplot(data, aes(x = Compression_Ratio, y = Time_s, color = Algorithm)) +
  geom_line(size = 1) +
  geom_point(size = 3) +
  labs(title = "Compression Ratio vs Time", x = "Compression Ratio", y = "Time (s)") +
  custom_theme
