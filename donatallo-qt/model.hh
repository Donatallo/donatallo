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

#ifndef DONATALLO_QT_MODEL_HH
#define DONATALLO_QT_MODEL_HH

#include <QAbstractItemModel>

#include <libdonatallo/result.hh>

class Model : public QAbstractItemModel {
	Q_OBJECT
private:
	Donatallo::Result result_;

public:
	Model(Donatallo::Result result, QObject* parent = nullptr);

	int rowCount(const QModelIndex& parent = QModelIndex()) const final;
	int columnCount(const QModelIndex& parent = QModelIndex()) const final;
	QVariant data(const QModelIndex &index = QModelIndex(), int role = Qt::DisplayRole) const final;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const final;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const final;
	QModelIndex parent(const QModelIndex &index = QModelIndex()) const final;
};

#endif
