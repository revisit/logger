
// "groups": [
//     {
//         "name": "sphere-test",
//         "objs": [
//             {
//                 "type": "sphere",
//                 "color": "0x0000ff",
//                 "radius": 100
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

#include <unordered_map>


namespace revisit
{
class logger
{

private:
    json log_data_;
    std::unordered_map<std::string, std::array<double, 7>> positions_;

public:
    logger(double start, double step, double stop) {
        log_data_["start"] = start;
        log_data_["step"] = step;
        log_data_["stop"] = stop;
    }

    void add_sphere(const std::string & name, double radius) {
        log_data_["groups"].push_back({
            {"name", name},
            {"objs", {{
                {"type", "sphere"},
                {"color", "0x0000ff"},
                {"radius", radius}
            }} }
        });
    }

    void add_box(const std::string & name, double x_size, double y_size, double z_size) {
        log_data_["groups"].push_back({
            {"name", name},
            {"objs", {{
                {"type", "box"},
                {"color", "0xcccccc"},
                {"scale", {x_size, y_size, z_size}}
            }} }
        });
    }

    void add_cylinder(const std::string & name, double radius, double height) {
        log_data_["groups"].push_back({
            {"name", name},
            {"objs", {{
                {"type", "cylinder"},
                {"color", "0x0000ff"},
                {"scale", {radius, radius, height}},
                {"vertical", "z"}
            }} }
        });
    }

    void add_ellipsoid(const std::string & name, double x_size, double y_size, double z_size) {
        log_data_["groups"].push_back({
            {"name", name},
            {"objs", {{
                {"type", "ellipsoid"},
                {"color", "0xccccff"},
                {"scale", {x_size, y_size, z_size}}
            }} }
        });
    }

    void new_frame() {
        log_data_["frames"].push_back({});
    }

    void add_to_frame(const std::string & name,
        double x, double y, double z,
        double qx, double qy, double qz, double qw) {

        if (enough_motion(name, x, y, z, qx, qy, qz, qw)) {
            log_data_["frames"].back()[name] = {
                {"position", {x, y, z}},
                {"quaternion", {qx, qy, qz, qw}}
            };
            positions_[name] = std::array<double, 7>{{x, y, z, qx, qy, qz, qw}};
        }
    }

    void add_frame(const std::string & name,
        double x, double y, double z,
        double qx, double qy, double qz, double qw) {

        new_frame();
        add_to_frame(name, x, y, z, qx, qy, qz, qw);
    }

    auto to_string(bool pretty=true) const {
        return log_data_.dump(pretty ? 4 : -1);
    }

    bool enough_motion(const std::string & name,
        double x, double y, double z,
        double qx, double qy, double qz, double qw,
        double trans_tol = 1, double quat_tol = 0.01) {

        return positions_.find(name) == positions_.end()
            || abs(x - positions_[name][0]) > trans_tol
            || abs(y - positions_[name][1]) > trans_tol
            || abs(z - positions_[name][2]) > trans_tol
            || abs(qx - positions_[name][3]) > quat_tol
            || abs(qy - positions_[name][4]) > quat_tol
            || abs(qz - positions_[name][5]) > quat_tol
            || abs(qw - positions_[name][6]) > quat_tol;
    }
};

}

#endif
