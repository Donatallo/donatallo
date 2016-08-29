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

#ifndef DONATALLO_QT_PROJECTDELEGATEL_HH
#define DONATALLO_QT_PROJECTDELEGATEL_HH

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QSize>
#include <QMap>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class QPainter;
QT_END_NAMESPACE

class ProjectDelegate : public QStyledItemDelegate {
	Q_OBJECT
private:
	struct ProjectItemData {
		QString name;
		QString comment;

		QFont header_font;

		QRect name_rect;
		QRect comment_rect;

		QRect total_item_rect;
	};

	struct DonationMethodData {
		QString name;
		QPixmap icon;
	};

private:
	QMap<QString, DonationMethodData> donation_methods_;

public:
	ProjectDelegate(QObject *parent = nullptr);

	void addDonationMethod(const QString& method, const QString& name, const QString& iconpath = "");

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
	ProjectItemData GetProjectItemData(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif
