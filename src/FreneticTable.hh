#pragma once
#include "Application.hh"
#include "Loader.hh"
#include "SwitchConnectionFwd.hh"
#include "Common.hh"

class FreneticTable : public Application {
SIMPLE_APPLICATION(FreneticTable, "frenetic-fwd")
public:
    void init(Loader* loader, const Config& config) override;
private slots:
    void onSwitchUp(runos::SwitchConnectionPtr conn, of13::FeaturesReply fr);

private:
    class Controller* m_ctrl;
    uint8_t m_table;
    uint64_t m_meta;
};
