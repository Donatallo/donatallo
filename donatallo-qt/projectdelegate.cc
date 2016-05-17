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

#include <libdonatallo/project.hh>

#include "projectdelegate.hh"

constexpr int ProjectDelegate::project_cell_margin_;
constexpr int ProjectDelegate::project_name_bottom_spacing_;
constexpr int ProjectDelegate::project_name_right_shift_;
constexpr float ProjectDelegate::project_name_font_size_multiplier_;

constexpr int ProjectDelegate::payment_method_icon_size_;
constexpr int ProjectDelegate::payment_method_icon_spacing_;
constexpr int ProjectDelegate::payment_method_icon_rounding_;

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
	} else if (index.column() == 1) {
		QStringList methods = index.data().toString().split(" ");

		QSize icons_size(payment_method_icon_size_ * methods.size() + payment_method_icon_spacing_ * (methods.size() - 1), payment_method_icon_size_);

		int n = -1;
		for (auto& method : methods) {
			n++;

			QRect target_rect(
				option.rect.left() + (option.rect.width() - icons_size.width()) / 2 + n * (payment_method_icon_size_ + payment_method_icon_spacing_),
				option.rect.top() + (option.rect.height() - icons_size.height()) / 2,
				payment_method_icon_size_,
				payment_method_icon_size_
			);

			auto icon = payment_method_icons_.find(method);
			if (icon != payment_method_icons_.end()) {
				painter->drawPixmap(target_rect, *icon);
			} else {
				painter->setPen(Qt::NoPen);
				painter->setBrush(QColor::fromHsv((qHash(method) >> 5) % 360, 128, 192));
				painter->setRenderHint(QPainter::Antialiasing);
				painter->drawRoundedRect(target_rect, payment_method_icon_rounding_, payment_method_icon_rounding_);

				painter->setPen(Qt::white);
				painter->drawText(target_rect.marginsRemoved(QMargins(2, 2, 2, 2)), Qt::AlignHCenter | Qt::TextWrapAnywhere,
					// XXX: lol, simplify this
					QString::fromStdString(
						Donatallo::Project::DonationMethodToHumanReadable(
							Donatallo::Project::DonationMethodFromKeyword(
								method.toStdString()
							)
						)
					)
				);
			}
		}
	}

	painter->restore();
}

QSize ProjectDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
	if (index.column() == 0) {
		ProjectItemData itemdata = GetProjectItemData(option, index);
		return itemdata.total_item_rect.size();
	} else {
		QStringList methods = index.data().toString().split(" ");
		return QSize(payment_method_icon_size_ * methods.size() + payment_method_icon_spacing_ * (methods.size() - 1), payment_method_icon_size_);
	}
}

ProjectDelegate::ProjectItemData ProjectDelegate::GetProjectItemData(const QStyleOptionViewItem &option, const QModelIndex &index) const {
	ProjectItemData data;
	data.name = index.data().toList()[0].toString();
	data.comment = index.data().toList()[1].toString();

	int font_height = QFontMetrics(option.font).height();
	int header_font_height = (int)(font_height * project_name_font_size_multiplier_);

	data.header_font = option.font;
	data.header_font.setWeight(QFont::Bold);
	data.header_font.setPixelSize(header_font_height);

	// note that the rects are approximate
	data.name_rect = QFontMetrics(data.header_font).boundingRect(data.name);
	data.comment_rect = QFontMetrics(option.font).boundingRect(data.comment);

	data.name_rect.moveTo(
		option.rect.topLeft() + QPoint(project_cell_margin_ + project_name_right_shift_, project_cell_margin_)
	);
	data.comment_rect.moveTo(
		option.rect.topLeft() + QPoint(project_cell_margin_, project_cell_margin_ + data.name_rect.height() + project_name_bottom_spacing_)
	);

	data.total_item_rect = (data.name_rect | data.comment_rect).marginsAdded(
		QMargins(project_cell_margin_, project_cell_margin_, project_cell_margin_, project_cell_margin_)
	);

	return data;
}
