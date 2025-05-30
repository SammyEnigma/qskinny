/******************************************************************************
 * QSkinny - Copyright (C) The authors
 *           SPDX-License-Identifier: BSD-3-Clause
 *****************************************************************************/

#ifndef QSK_INPUT_PANEL_BOX_H
#define QSK_INPUT_PANEL_BOX_H

#include "QskBox.h"

class QskInputEngine;
class QskVirtualKeyboard;

class QString;
class QLocale;

class QSK_EXPORT QskInputPanelBox : public QskBox
{
    Q_OBJECT

    using Inherited = QskBox;

    Q_PROPERTY( PanelHints panelHints READ panelHints
        WRITE setPanelHints NOTIFY panelHintsChanged )

    Q_PROPERTY( QString inputPrompt READ inputPrompt
        WRITE setInputPrompt NOTIFY inputPromptChanged )

  public:
    QSK_SUBCONTROLS( Panel, ProxyPanel, ProxyText )

    enum PanelHint : quint8
    {
        InputProxy = 1 << 0,
        Prediction = 1 << 1
    };

    Q_ENUM( PanelHint )
    Q_DECLARE_FLAGS( PanelHints, PanelHint )

    QskInputPanelBox( QQuickItem* parent = nullptr );
    ~QskInputPanelBox() override;

    void attachInputItem( QQuickItem* );
    QQuickItem* attachedInputItem() const;

    void setPanelHint( PanelHint, bool on );

    void setPanelHints( PanelHints );
    PanelHints panelHints() const;

    QQuickItem* inputProxy() const;

    QString inputPrompt() const;

    void setKeyboard( QskVirtualKeyboard* );

  Q_SIGNALS:
    void panelHintsChanged();
    void inputPromptChanged( const QString& );

    void keySelected( int keyCode );
    void predictiveTextSelected( int );

  public Q_SLOTS:
    void setInputPrompt( const QString& );
    void setPrediction( const QStringList& );

  protected:
    void keyPressEvent( QKeyEvent* ) override;

    QskAspect::Subcontrol substitutedSubcontrol(
        QskAspect::Subcontrol ) const override;

  private:
    class PrivateData;
    std::unique_ptr< PrivateData > m_data;
};

Q_DECLARE_OPERATORS_FOR_FLAGS( QskInputPanelBox::PanelHints )
Q_DECLARE_METATYPE( QskInputPanelBox::PanelHints )

#endif
