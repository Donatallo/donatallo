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

#include "model.hh"

Model::Model(Donatallo::Result result, QObject* parent) : QAbstractItemModel(parent), result_(result) {
}

int Model::rowCount(const QModelIndex& parent) const {
	if (!parent.isValid())
		return result_.size();

	return 0;
}

int Model::columnCount(const QModelIndex& parent) const {
	Q_UNUSED(parent);
	return 2;
}

QVariant Model::data(const QModelIndex &index, int role) const {
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	if (index.column() == 0)
		return QString::fromStdString(result_[index.row()].name);
	else if (index.column() == 1)
		return "Donat";

	return QVariant();
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const {
	if (parent.isValid())
		return QModelIndex();

	return createIndex(row, column, nullptr);
}

QModelIndex Model::parent(const QModelIndex &index) const {
	Q_UNUSED(index);
	return QModelIndex();
}
