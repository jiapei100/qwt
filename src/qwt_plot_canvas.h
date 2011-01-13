/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef QWT_PLOT_CANVAS_H
#define QWT_PLOT_CANVAS_H

#include "qwt_global.h"
#include <qframe.h>
#include <qpen.h>

class QwtPlot;
class QPixmap;

/*!
  \brief Canvas of a QwtPlot.
  \sa QwtPlot
*/
class QWT_EXPORT QwtPlotCanvas : public QFrame
{
    Q_OBJECT

public:

    /*!
      \brief Paint attributes

      - PaintCached\n
        Paint double buffered and reuse the content of the pixmap buffer
        for some spontaneous repaints that happen when a plot gets unhidden,
        deiconified or changes the focus.
        Disabling the cache will improve the performance for
        incremental paints (using QwtPlotCurve::draw).

      \sa setPaintAttribute(), testPaintAttribute(), paintCache()
     */
    enum PaintAttribute
    {
        PaintCached = 1,
    };

    /*!
      \brief Focus indicator

      - NoFocusIndicator\n
        Don't paint a focus indicator

      - CanvasFocusIndicator\n
        The focus is related to the complete canvas.
        Paint the focus indicator using paintFocus()

      - ItemFocusIndicator\n
        The focus is related to an item (curve, point, ...) on
        the canvas. It is up to the application to display a
        focus indication using f.e. highlighting.

      \sa setFocusIndicator(), focusIndicator(), paintFocus()
    */

    enum FocusIndicator
    {
        NoFocusIndicator,
        CanvasFocusIndicator,
        ItemFocusIndicator
    };

    explicit QwtPlotCanvas( QwtPlot * );
    virtual ~QwtPlotCanvas();

    QwtPlot *plot();
    const QwtPlot *plot() const;

    void setFocusIndicator( FocusIndicator );
    FocusIndicator focusIndicator() const;

    void setPaintAttribute( PaintAttribute, bool on = true );
    bool testPaintAttribute( PaintAttribute ) const;

    QPixmap *paintCache();
    const QPixmap *paintCache() const;
    void invalidatePaintCache();

    void replot();

protected:
    virtual void paintEvent( QPaintEvent * );

    virtual void drawBackground( QPainter * );
    virtual void drawContents( QPainter * );
    virtual void drawFocusIndicator( QPainter * );

    void drawCanvas( QPainter *painter = NULL );

private:
    class PrivateData;
    PrivateData *d_data;
};

#endif