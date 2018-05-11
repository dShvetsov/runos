#include "Firewall.hh"

#include "Maple.hh"
#include "Common.hh"
#include "types/ethaddr.hh"
#include "types/IPv4Addr.hh"
#include "oxm/openflow_basic.hh"

REGISTER_APPLICATION(Firewall, {"maple"})

using namespace runos;

void Firewall::init(Loader* loader, const Config& root_config)
{
    auto maple = Maple::get(loader);
    const auto ofb_eth_src = oxm::eth_src();
    const auto ofb_eth_dst = oxm::eth_dst();
    const auto ofb_eth_type = oxm::eth_type();
    const auto ofb_ipv4_src = oxm::ipv4_src();
    const auto ofb_ip_proto = oxm::ip_proto();

    maple->registerHandler("firewall", [=](Packet& pkt, FlowPtr, Decision decision)
            {
                bool bad_src = pkt.test(ofb_eth_src == "00:00:00:00:00:01");
                bool bad_dst = pkt.test(ofb_eth_src == "00:00:00:00:00:01");
                bool is_ip = pkt.test(ofb_eth_type == 0x800);
                bool bad_ip_src = is_ip and pkt.test(ofb_ipv4_src == "10.0.0.1");;
                bool is_udp = is_ip and pkt.test(ofb_ip_proto == 17);
                bool bad_udp = is_udp and pkt.test(ofb_ipv4_src == "10.0.0.3");
                bool bad_connection = pkt.test(ofb_eth_src == "00:00:00:00:00:03") and
                                      pkt.test(ofb_eth_dst == "00:00:00:00:00:02");
                if (bad_src or bad_dst or bad_ip_src or bad_udp or bad_connection) {
                    LOG(WARNING) << "Traffic blocked";
                    return decision.drop().return_();
                } else {
                    return decision;
                }
            });
}

