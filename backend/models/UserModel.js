import sequelize from "sequelize";
import db from "../config/Database.js";

const { DataTypes } = sequelize;

const Users = db.define(
  "users",
  {
    name: {
      type: DataTypes.STRING,
    },
    email: {
      type: DataTypes.STRING,
    },
    password: {
      type: DataTypes.STRING,
    },
    tabel: {
      type: DataTypes.INTEGER,
    },
    refresh_token: {
      type: DataTypes.TEXT,
    },
  },
  {
    freezeTableName: true,
  }
);

export default Users;
