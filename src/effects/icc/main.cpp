#include "icc.h"

namespace KWin
{

KWIN_EFFECT_FACTORY_SUPPORTED(ICCEffect,
                              "metadata.json.stripped",
                              return ICCEffect::supported();)

} // namespace KWin

#include "main.moc"
