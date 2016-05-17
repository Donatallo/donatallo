/*
 * Copyright (C) 2016 Dmitry Marakasov
 *
 * This file is part of donatallo.
 *
 * donatallo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * donatallo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with donatallo.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QPainter>
#include <QDirIterator>

#include "projectdelegate.hh"

ProjectDelegate::ProjectDelegate(QObject *parent) : QStyledItemDelegate(parent) {
	QDirIterator it(DONATALLO_DATADIR "/database/payment_icons/", { "*.png" }, QDir::Files);
	while (it.hasNext()) {
		it.next();
		QString name = it.fileName();
		name.chop(4);
		payment_method_icons_[name] = QPixmap(it.filePath());
	}
}

void ProjectDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	// fill background
	if (option.state & QStyle::State_Selected) {
		painter->fillRect(option.rect, option.palette.highlight());
	} else if (index.row() % 2) {
		painter->fillRect(option.rect, option.palette.alternateBase());
	}

	painter->save();

	painter->setClipRect(option.rect);

	if (index.column() == 0) {
		ProjectItemData itemdata = GetProjectItemData(option, index);

		// draw texts
		if (option.state & QStyle::State_Selected)
			painter->setPen(option.palette.highlightedText().color());
		else
			painter->setPen(option.palette.text().color());

		painter->setFont(itemdata.header_font);
		painter->drawText(itemdata.name_rect, Qt::AlignLeft | Qt::AlignTop | Qt::TextDontClip, itemdata.name);

		painter->setFont(option.font);
		painter->drawText(itemdata.comment_rect, Qt::AlignLeft | Qt::AlignTop | Qt::TextDontClip, itemdata.comment);

	} else {
		QStyledItemDelegate::paint(painter, option, index);
	}

	painter->restore();
}

QSize ProjectDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
	if (index.column() == 0) {
		ProjectItemData itemdata = GetProjectItemData(option, index);
		return itemdata.total_item_rect.size();
	} else {
		return QStyledItemDelegate::sizeHint(option, index);
	}
}

ProjectDelegate::ProjectItemData ProjectDelegate::GetProjectItemData(const QStyleOptionViewItem &option, const QModelIndex &index) const {
	constexpr static int margin = 5;
	constexpr static int header_bottom_spacing = margin;
	constexpr static int header_left_spacing = 10;
	constexpr static float header_size_multiplier = 1.2f;

	ProjectItemData data;
	data.name = index.data().toList()[0].toString();
	data.comment = index.data().toList()[1].toString();

	int font_height = QFontMetrics(option.font).height();
	int header_font_height = (int)(font_height * header_size_multiplier);

	data.header_font = option.font;
	data.header_font.setWeight(QFont::Bold);
	data.header_font.setPixelSize(header_font_height);

	// note that the rects are approximate
	data.name_rect = QFontMetrics(data.header_font).boundingRect(data.name);
	data.comment_rect = QFontMetrics(option.font).boundingRect(data.comment);

	data.name_rect.moveTo(option.rect.topLeft() + QPoint(margin + header_left_spacing, margin));
	data.comment_rect.moveTo(option.rect.topLeft() + QPoint(margin, margin + data.name_rect.height() + header_bottom_spacing));

	data.total_item_rect = (data.name_rect | data.comment_rect).marginsAdded(QMargins(margin, margin, margin, margin));

	return data;
}
