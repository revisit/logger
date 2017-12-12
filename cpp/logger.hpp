
// "groups": [
//     {
//         "name": "sphere-test",
//         "objs": [
//             {
//                 "type": "sphere",
//                 "color": "0x0000ff",
//                 "diameter": 100
//             }
//         ]
//     }
// ],
// "step": 0.04,
// "start": 0,
// "stop": 0.04,
// "frames": [
//     {
//         "sphere-test": {
//             "position": [0, 0, 0],
//             "quaternion": [1,0,0,1]
//         }
//     },
//     {
//         "sphere-test": {
//             "position": [0, 0, 0],
//             "quaternion": [1,0,0,1]
//         }
//     }
// ]

#ifndef REVISIT_LOGGER_HPP
#define REVISIT_LOGGER_HPP


#include "json.hpp"
using json = nlohmann::json;


namespace revisit
{
class logger
{

private:
    json log_data_;

public:
    logger(double start, double step, double stop) {
        log_data_["start"] = start;
        log_data_["step"] = step;
        log_data_["stop"] = stop;
    }

    void add_group(const std::string & name, const std::string & type, double diameter) {
        log_data_["groups"].push_back({
            {"name", name},
            {"objs", {{
                {"type", type},
                {"color", "0x0000ff"},
                {"diameter", diameter}
            }} }
        });
    }

    void add_frame(const std::string & name,
        double x, double y, double z,
        double qx, double qy, double qz, double w) {
        log_data_["frames"].push_back({
            {name, {
                {"position", {x, y, z}},
                {"quaternion", {qx, qy, qz, w}}
            }}
        });
    }
};

}

#endif