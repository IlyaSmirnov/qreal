#include "regionItem.h"

#include <QtXml/QDomElement>
#include <QtGui/QPainter>

const QColor defaultColor = QColor(135, 206, 250);
const QSizeF defaultSize = QSizeF(200, 200);

using namespace twoDModel::items;

RegionItem::RegionItem(QGraphicsItem *parent)
	: QGraphicsItem(parent)
	, mTextItem(new QGraphicsTextItem(this))
	, mFilled(true)
	, mColor(defaultColor)
	, mSize(defaultSize)
{
}

QString RegionItem::id() const
{
	return mId;
}

void RegionItem::setId(const QString &id)
{
	mId = id;
}

bool RegionItem::filled() const
{
	return mFilled;
}

void RegionItem::setFilled(bool filled)
{
	mFilled = filled;
}

QString RegionItem::text() const
{
	return mTextItem->toPlainText();
}

void RegionItem::setText(const QString &text)
{
	mTextItem->setHtml(QString("<div style='background-color:#FFFFFF;color:%2;'>%1</div>")
			.arg(text, mColor.name()));
	mTextItem->setVisible(!text.isEmpty());
}

QPointF RegionItem::textPosition() const
{
	return mTextItem->pos();
}

void RegionItem::setTextPosition(const QPointF &pos)
{
	mTextItem->setPos(pos);
}

QColor RegionItem::color() const
{
	return mColor;
}

void RegionItem::setColor(const QColor &color)
{
	mColor = color;
	setText(text());  // To update text color
}

void RegionItem::setSize(const QSizeF &size)
{
	mSize = size;
}

QRectF RegionItem::boundingRect() const
{
	return QRectF(QPointF(), mSize);
}

void RegionItem::serialize(QDomElement &element)
{
	if (!id().isEmpty()) {
		element.setAttribute("id", id());
	}

	element.setAttribute("filled", filled() ? "true" : "false");

	if (!text().isEmpty()) {
		element.setAttribute("text", text());
		element.setAttribute("textX", textPosition().x());
		element.setAttribute("textY", textPosition().y());
	}

	QSizeF const size = boundingRect().size();
	element.setAttribute("height", size.height());
	element.setAttribute("width", size.width());
	element.setAttribute("x", pos().x());
	element.setAttribute("y", pos().y());

	element.setAttribute("visible", isVisible() ? "true" : "false");

	element.setAttribute("color", color().name());
}

void RegionItem::deserialize(const QDomElement &element)
{
	if (element.hasAttribute("id")) {
		setId(element.attribute("id"));
	}

	if (element.hasAttribute("filled")) {
		setFilled(element.attribute("filled") == "true");
	}

	if (element.hasAttribute("color")) {
		setColor(QColor(element.attribute("color")));
	}

	if (element.hasAttribute("text")) {
		setText(element.attribute("text"));
	}

	if (element.hasAttribute("textX") && element.hasAttribute("textY")) {
		setTextPosition(deserializePoint(element, "textX", "textY"));
	}

	if (element.hasAttribute("x") && element.hasAttribute("y")) {
		setPos(deserializePoint(element, "x", "y"));
	}

	if (element.hasAttribute("visible")) {
		setVisible(element.attribute("visible") == "true");
	}

	if (element.hasAttribute("height") && element.hasAttribute("width")) {
		const QString heightText = element.attribute("height");
		const QString widthText = element.attribute("width");
		bool heightOk = false;
		bool widthOk = false;
		const qreal height = heightText.toDouble(&heightOk);
		const qreal width = widthText.toDouble(&widthOk);
		if (heightOk && widthOk) {
			setSize(QSizeF(width, height));
		} /// @todo: else report error
	}
}

void RegionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	painter->save();
	painter->setPen(mColor);
	painter->setBrush(QBrush(mColor, mFilled ? Qt::BDiagPattern : Qt::NoBrush));
	painter->drawPath(shape());
	painter->restore();
}

QPointF RegionItem::deserializePoint(const QDomElement &element, const QString &xAttribute, const QString &yAttribute)
{
	const QString textX = element.attribute(xAttribute);
	const QString textY = element.attribute(yAttribute);
	bool xOk = false;
	bool yOk = false;
	const qreal x = textX.toDouble(&xOk);
	const qreal y = textY.toDouble(&yOk);
	if (xOk && yOk) {
		return QPointF(x, y);
	} /// @todo: else report error

	return QPointF();
}