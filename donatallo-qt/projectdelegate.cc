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

#include "projectdelegate.hh"

ProjectDelegate::ProjectDelegate(QObject *parent) : QStyledItemDelegate(parent) {
}

void ProjectDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	// fill background
	if (option.state & QStyle::State_Selected) {
		painter->fillRect(option.rect, option.palette.highlight());
	} else if (index.row() % 2) {
		painter->fillRect(option.rect, option.palette.alternateBase());
	}

	if (index.column() == 0) {
		int font_height = QFontMetrics(option.font).height();

		// bold font for header
		QFont bold_font = option.font;
		bold_font.setWeight(QFont::Bold);

		// data strings
		QString name = index.data().toList()[0].toString();
		QString comment = index.data().toList()[1].toString();

		// rects for text rendering
		QRectF name_rect = option.rect.marginsRemoved(QMargins(font_height/2, font_height/2, font_height/2, font_height/2));
		QRectF comment_rect = name_rect;
		comment_rect.setTop(comment_rect.top() + font_height * 1.5f);

		// draw texts
		painter->save();

		if (option.state & QStyle::State_Selected)
			painter->setPen(option.palette.highlightedText().color());
		else
			painter->setPen(option.palette.text().color());

		painter->setFont(bold_font);
		painter->drawText(name_rect, Qt::AlignLeft, "  " + name);

		painter->setFont(option.font);
		painter->drawText(comment_rect, Qt::AlignLeft, comment);

		painter->restore();
	} else {
		QStyledItemDelegate::paint(painter, option, index);
	}
}

QSize ProjectDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
	if (index.column() == 0) {
		int font_height = QFontMetrics(option.font).height();

		return QSize(10, font_height * (0.5f + 1.0f + 0.5f + 1.0f + 0.5f));
	} else {
		return QStyledItemDelegate::sizeHint(option, index);
	}
}
