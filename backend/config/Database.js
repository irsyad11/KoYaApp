import sequelize from "sequelize";

const db = new sequelize("koya_db", "root", "", {
  host: "localhost",
  dialect: "mysql",
});

export default db;
