/*
 *    Description:
 *        Created:  06/06/2019
 *         Author:  Yohan Pipereau
*/

#include <iostream>
#include <vom/hw.hpp>
#include <vom/om.hpp>

#include <vom/interface_cmds.hpp>

using namespace std;
using namespace VOM;

int main()
{
    std::cout << "Connect to VOM" << "\n"
              << "Please run as root"
              << std::endl;
    /* Init connection to VPP */
    HW::init(new HW::cmd_q());
    /* Init connection to VOM database */
    OM::init();
    while (HW::connect() != true);

    cout << "connection successful" << endl;

    shared_ptr<interface_cmds::dump_cmd> cmd =
        make_shared<interface_cmds::dump_cmd>();
    HW::enqueue(cmd);
    HW::write();

    for (auto &itf : *cmd) {
        vapi_payload_sw_interface_details payload = itf.get_payload();
        cout << "name:" << payload.interface_name << "\n\t"
             << "mtu L3:" << payload.mtu[0] << "\n\t"
             << "mtu IP4:" << payload.mtu[1] << "\n\t"
             << "mtu IP6:" << payload.mtu[2] << "\n\t"
             << "mtu MPLS:" << payload.mtu[3] << "\n\t"
             << "link mtu:" << payload.link_mtu
             << endl;
    }

    HW::disconnect();
    std::cout << "Disconnect from VOM" << std::endl;

    return 0;
}


