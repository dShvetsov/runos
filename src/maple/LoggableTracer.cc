#include "LoggableTracer.hh"
#include "oxm/field.hh"

namespace runos {
namespace maple {

void LoggableTracer::load(oxm::field<> unexplored)
{
    m_log << "(L " << unexplored << ") ";
    m_wrapee.load(unexplored);
}

void LoggableTracer::vload(oxm::field<> by, oxm::field<> what)
{
    m_log << "V " << what << " by " << by << ") ";
    m_wrapee.vload(by, what);
}

void LoggableTracer::test(oxm::field<> pred, bool ret)
{
    m_log << "(T " << pred << " -> " << ret << ") ";
    m_wrapee.test(pred, ret);
}

Installer LoggableTracer::finish(FlowPtr flow)
{
    m_log << "F";
    return m_wrapee.finish(flow);
}

LoggableTracer::~LoggableTracer() = default;

} // namespace maple
} // namespace runos
