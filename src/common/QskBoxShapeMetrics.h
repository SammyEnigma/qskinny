/******************************************************************************
 * QSkinny - Copyright (C) The authors
 *           SPDX-License-Identifier: BSD-3-Clause
 *****************************************************************************/

#ifndef QSK_BOX_SHAPE_METRICS_H
#define QSK_BOX_SHAPE_METRICS_H

#include "QskGlobal.h"

#include <qmetatype.h>
#include <qnamespace.h>
#include <qsize.h>

class QVariant;

class QSK_EXPORT QskBoxShapeMetrics
{
    Q_GADGET

    Q_PROPERTY( QSizeF topLeft READ topLeft WRITE setTopLeft )
    Q_PROPERTY( QSizeF topRight READ topRight WRITE setTopRight )
    Q_PROPERTY( QSizeF bottomLeft READ bottomLeft WRITE setBottomLeft )
    Q_PROPERTY( QSizeF bottomRight READ bottomRight WRITE setBottomRight )

    Q_PROPERTY( qreal radius READ radiusX WRITE setRadius )

    Q_PROPERTY( Qt::SizeMode sizeMode READ sizeMode WRITE setSizeMode )
    Q_PROPERTY( ScalingMode scalingMode READ scalingMode WRITE setScalingMode )

  public:
    /*
        How to scale, when translating to Qt::AbsoluteSize

        Symmetric/SymmetricByMaximum sets the aspect ratio between x/y radii
        to 1:1, while Proportional preserves the aspect ratio of the relative radii.

        Symmetric or Proportional shrink the larger radius, while SymmetricByMaximum
        expands the smaller radius to achieve the desired aspect ratio.

        The effect of the scaling on the implemented box rendering is:

        - SymmetricByMaximum in combination with a relative radius of 100
          results in an ellipse.

        - Rectangles with rounded corners can be achieved by Symmetric in combination
          with a relative radius < 100.

        Note, that the scaling is affected by the aspect ratio of the relative radii and
        the one of the absolute size.

        The default setting is Symmetric.
     */

    enum ScalingMode : quint8
    {
        Symmetric,
        SymmetricByMaximum,

        Proportional
    };
    Q_ENUM( ScalingMode )

    constexpr QskBoxShapeMetrics() noexcept;

    constexpr QskBoxShapeMetrics( qreal topLeft, qreal topRight,
        qreal bottomLeft, qreal bottomRight, Qt::SizeMode = Qt::AbsoluteSize ) noexcept;

    constexpr QskBoxShapeMetrics(
        qreal radius, Qt::SizeMode = Qt::AbsoluteSize ) noexcept;

    constexpr QskBoxShapeMetrics( qreal radiusX, qreal radiusY,
        Qt::SizeMode = Qt::AbsoluteSize ) noexcept;

    constexpr bool operator==( const QskBoxShapeMetrics& ) const noexcept;
    constexpr bool operator!=( const QskBoxShapeMetrics& ) const noexcept;

    void setRadius( qreal radius ) noexcept;
    void setRadius( qreal radius, Qt::SizeMode ) noexcept;
    void setRadius( Qt::Corner, qreal radius ) noexcept;

    void setRadius( qreal radiusX, qreal radiusY ) noexcept;
    void setRadius( const QSizeF& ) noexcept;
    void setRadius( Qt::Corner, qreal radiusX, qreal radiusY ) noexcept;
    void setRadius( Qt::Corner, const QSizeF& radius ) noexcept;

    void setRadius( qreal topLeft, qreal topRight,
        qreal bottomLeft, qreal bottomRight ) noexcept;

    void setRadius( const QSizeF& topLeft, const QSizeF& topRight,
        const QSizeF& bottomLeft, const QSizeF& bottomRight ) noexcept;

    void setRadius(
        qreal topLeftX, qreal topLeftY,
        qreal topRightX, qreal topRightY,
        qreal bottomLeftX, qreal bottomLeftY,
        qreal bottomRightX, qreal bottomRightY ) noexcept;

    constexpr QSizeF radius( Qt::Corner ) const noexcept;

    constexpr QSizeF topLeft() const noexcept;
    constexpr QSizeF topRight() const noexcept;
    constexpr QSizeF bottomLeft() const noexcept;
    constexpr QSizeF bottomRight() const noexcept;

    void setTopLeft( const QSizeF& ) noexcept;
    void setTopRight( const QSizeF& ) noexcept;
    void setBottomLeft( const QSizeF& ) noexcept;
    void setBottomRight( const QSizeF& ) noexcept;

    constexpr bool isRectangle() const noexcept;
    constexpr bool isRectellipse() const noexcept;

    void setSizeMode( Qt::SizeMode ) noexcept;
    constexpr Qt::SizeMode sizeMode() const noexcept;

    void setScalingMode( ScalingMode ) noexcept;
    constexpr ScalingMode scalingMode() const noexcept;

    QskBoxShapeMetrics interpolated(
        const QskBoxShapeMetrics&, qreal value ) const noexcept;

    QskBoxShapeMetrics toAbsolute( const QSizeF& ) const noexcept;

    constexpr QskBoxShapeMetrics transposed() const noexcept;

    QskHashValue hash( QskHashValue seed = 0 ) const noexcept;

    static QVariant interpolate( const QskBoxShapeMetrics&,
        const QskBoxShapeMetrics&, qreal progress ) noexcept;

  private:
    // dummy getter to suppress moc warnings
    inline qreal radiusX() const { return radius( Qt::TopLeftCorner ).width(); }

    inline constexpr QskBoxShapeMetrics(
            const QSizeF& topLeft, const QSizeF& topRight,
            const QSizeF& bottomLeft, const QSizeF& bottomRight,
            Qt::SizeMode sizeMode, ScalingMode scalingMode ) noexcept
        : m_radii{ topLeft, topRight, bottomLeft, bottomRight }
        , m_sizeMode( sizeMode )
        , m_scalingMode( scalingMode )
    {
    }

    QSizeF m_radii[ 4 ];
    unsigned int m_sizeMode : 2;
    ScalingMode m_scalingMode : 2;
};

inline constexpr QskBoxShapeMetrics::QskBoxShapeMetrics() noexcept
    : m_radii{ { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } }
    , m_sizeMode( Qt::AbsoluteSize )
    , m_scalingMode( Symmetric )
{
}

inline constexpr QskBoxShapeMetrics::QskBoxShapeMetrics(
        qreal radius, Qt::SizeMode sizeMode ) noexcept
    : QskBoxShapeMetrics( radius, radius, sizeMode )
{
}

inline constexpr QskBoxShapeMetrics::QskBoxShapeMetrics(
        qreal radiusX, qreal radiusY, Qt::SizeMode sizeMode ) noexcept
    : m_radii{ { radiusX, radiusY }, { radiusX, radiusY },
        { radiusX, radiusY }, { radiusX, radiusY } }
    , m_sizeMode( sizeMode )
    , m_scalingMode( Symmetric )
{
}

inline constexpr QskBoxShapeMetrics::QskBoxShapeMetrics( qreal topLeft, qreal topRight,
        qreal bottomLeft, qreal bottomRight, Qt::SizeMode sizeMode ) noexcept
    : m_radii{ { topLeft, topLeft }, { topRight, topRight },
        { bottomLeft, bottomLeft }, { bottomRight, bottomRight } }
    , m_sizeMode( sizeMode )
    , m_scalingMode( Symmetric )
{
}

inline constexpr bool QskBoxShapeMetrics::operator==(
    const QskBoxShapeMetrics& other ) const noexcept
{
    return ( m_sizeMode == other.m_sizeMode )
        && ( m_scalingMode == other.m_scalingMode )
        && ( m_radii[ 0 ] == other.m_radii[ 0 ] )
        && ( m_radii[ 1 ] == other.m_radii[ 1 ] )
        && ( m_radii[ 2 ] == other.m_radii[ 2 ] )
        && ( m_radii[ 3 ] == other.m_radii[ 3 ] );
}

inline constexpr bool QskBoxShapeMetrics::operator!=(
    const QskBoxShapeMetrics& other ) const noexcept
{
    return !( *this == other );
}

inline void QskBoxShapeMetrics::setRadius( qreal radius ) noexcept
{
    setRadius( radius, radius );
}

inline void QskBoxShapeMetrics::setRadius( qreal radius, Qt::SizeMode sizeMode ) noexcept
{
    setRadius( radius );
    setSizeMode( sizeMode );
}

inline void QskBoxShapeMetrics::setRadius( qreal radiusX, qreal radiusY ) noexcept
{
    setRadius( radiusX, radiusY, radiusX, radiusY,
        radiusX, radiusY, radiusX, radiusY );
}

inline void QskBoxShapeMetrics::setRadius( const QSizeF& radius ) noexcept
{
    setRadius( radius.width(), radius.height() );
}

inline void QskBoxShapeMetrics::setRadius( Qt::Corner corner, qreal radius ) noexcept
{
    setRadius( corner, radius, radius );
}

inline void QskBoxShapeMetrics::setRadius( Qt::Corner corner, const QSizeF& radius ) noexcept
{
    setRadius( corner, radius.width(), radius.height() );
}

inline void QskBoxShapeMetrics::setRadius(
    qreal topLeft, qreal topRight, qreal bottomLeft, qreal bottomRight ) noexcept
{
    setRadius( topLeft, topLeft, topRight, topRight,
        bottomLeft, bottomLeft, bottomRight, bottomRight );
}

inline void QskBoxShapeMetrics::setRadius(
    const QSizeF& topLeft, const QSizeF& topRight,
    const QSizeF& bottomLeft, const QSizeF& bottomRight ) noexcept
{
    setRadius( topLeft.width(), topLeft.height(),
        topRight.width(), topRight.height(),
        bottomLeft.width(), bottomLeft.height(),
        bottomRight.width(), bottomRight.height() );
}

inline constexpr QSizeF QskBoxShapeMetrics::radius( Qt::Corner corner ) const noexcept
{
    return ( ( static_cast< int >( corner ) >= 0 ) && ( static_cast< int >( corner ) < 4 ) )
        ? m_radii[ corner ] : QSizeF();
}

inline constexpr QSizeF QskBoxShapeMetrics::topLeft() const noexcept
{
    return radius( Qt::TopLeftCorner );
}

inline constexpr QSizeF QskBoxShapeMetrics::topRight() const noexcept
{
    return radius( Qt::TopRightCorner );
}

inline constexpr QSizeF QskBoxShapeMetrics::bottomLeft() const noexcept
{
    return radius( Qt::BottomLeftCorner );
}

inline constexpr QSizeF QskBoxShapeMetrics::bottomRight() const noexcept
{
    return radius( Qt::BottomRightCorner );
}

inline void QskBoxShapeMetrics::setSizeMode( Qt::SizeMode sizeMode ) noexcept
{
    m_sizeMode = sizeMode;
}

inline constexpr Qt::SizeMode QskBoxShapeMetrics::sizeMode() const noexcept
{
    return static_cast< Qt::SizeMode >( m_sizeMode );
}

inline void QskBoxShapeMetrics::setScalingMode( ScalingMode scalingMode ) noexcept
{
    m_scalingMode = scalingMode;
}

inline constexpr QskBoxShapeMetrics::ScalingMode
    QskBoxShapeMetrics::scalingMode() const noexcept
{
    return m_scalingMode;
}

inline constexpr bool QskBoxShapeMetrics::isRectellipse() const noexcept
{
    return ( m_radii[ 1 ] == m_radii[ 0 ] )
        && ( m_radii[ 2 ] == m_radii[ 1 ] )
        && ( m_radii[ 3 ] == m_radii[ 2 ] );
}

inline constexpr bool QskBoxShapeMetrics::isRectangle() const noexcept
{
    return ( ( ( m_radii[ 0 ].width() <= 0.0 ) && ( m_radii[ 0 ].height() <= 0.0 ) )
        && ( ( m_radii[ 1 ].width() <= 0.0 ) && ( m_radii[ 1 ].height() <= 0.0 ) )
        && ( ( m_radii[ 2 ].width() <= 0.0 ) && ( m_radii[ 2 ].height() <= 0.0 ) )
        && ( ( m_radii[ 3 ].width() <= 0.0 ) && ( m_radii[ 3 ].height() <= 0.0 ) ) );
}

inline constexpr QskBoxShapeMetrics QskBoxShapeMetrics::transposed() const noexcept
{
    return QskBoxShapeMetrics(
        m_radii[ 0 ].transposed(), m_radii[ 1 ].transposed(),
        m_radii[ 2 ].transposed(), m_radii[ 3 ].transposed(),
        sizeMode(), m_scalingMode );
}

#ifndef QT_NO_DEBUG_STREAM

QSK_EXPORT QDebug operator<<( QDebug, const QskBoxShapeMetrics& );

#endif

Q_DECLARE_TYPEINFO( QskBoxShapeMetrics, Q_MOVABLE_TYPE );
Q_DECLARE_METATYPE( QskBoxShapeMetrics )

#endif
