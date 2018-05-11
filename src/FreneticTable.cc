#include "FreneticTable.hh"

#include "Controller.hh"
#include "Common.hh"

REGISTER_APPLICATION(FreneticTable, {"controller"})

using namespace runos;

void FreneticTable::init(Loader* loader, const Config& root_config)
{
    auto m_ctrl = Controller::get(loader);
    QObject::connect(
            m_ctrl, &Controller::switchUp,
            this, &FreneticTable::onSwitchUp
        );
    m_table = m_ctrl->getTable("frenetic-fwd");
    auto config = config_cd(root_config, "frenetic-fwd");
    m_meta = config_get(config, "meta", 0);
    m_ctrl->clearMyTablePlease(m_table);
    LOG(INFO) << "Use table : " << (int)m_table << "Meta : " << m_meta;
}

void FreneticTable::onSwitchUp(SwitchConnectionPtr connection, of13::FeaturesReply fr)
{
    of13::FlowMod fm;
    fm.command(of13::OFPFC_ADD);
    fm.priority(42);
    fm.cookie(0);
    fm.idle_timeout(0);
    fm.hard_timeout(0);
    fm.table_id(m_table);
    fm.flags(of13::OFPFF_CHECK_OVERLAP | of13::OFPFF_SEND_FLOW_REM);
    fm.add_oxm_field(new of13::Metadata(m_meta));
    of13::GoToTable go_to_table(m_table + 1);
    fm.add_instruction(go_to_table);

    connection->send(fm);
    LOG(WARNING) << "Install goto message";
}
