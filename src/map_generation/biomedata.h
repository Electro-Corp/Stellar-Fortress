#ifndef BIOMEDATA_H
#define BIOMEDATA_H

class BiomeData {
private:
    std::vector<float> height_nodes;
    std::vector<float> heat_nodes;
    std::vector<float> humidity_nodes;


    float avg_height;
    float avg_heat;
    float avg_humidity;

    float average(const std::vector<float> &vals) {
      auto sum = std::reduce(
        vals.begin(),
        vals.end(),
        (float) 0,
        std::plus<float>()
      );

      return sum / vals.size();
    }

  public:
    
    void add_node(float height, float heat, float humidity) {
      height_nodes.push_back(height);
      heat_nodes.push_back(heat);
      humidity_nodes.push_back(humidity);
    }

    void compute_averages() {
      avg_height = average(height_nodes);
      avg_heat = average(heat_nodes);
      avg_humidity = average(humidity_nodes);
    }

    float average_height() const { return avg_height; }
    float average_heat() const { return avg_heat; }
    float average_humidity() const { return avg_humidity; }

    int biome_index;
};
#endif