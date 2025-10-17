############################################################################
# QSkinny - Copyright (C) The authors
#           SPDX-License-Identifier: BSD-3-Clause
############################################################################

set(SOURCES main.cpp)
set(target systemdialogs)

qsk_add_example(${target} ${SOURCES})

target_link_libraries(${target} PRIVATE
    Qt::QuickDialogs2Private
    Qt::QuickDialogs2UtilsPrivate
)

if(QT_VERSION_MINOR VERSION_GREATER_EQUAL 10)
    target_link_libraries(${target} PRIVATE
        Qt::QuickTemplates2Private
    )
endif()
