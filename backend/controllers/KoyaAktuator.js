import KoyaAktuator from "../models/KoyaAktuatorModel.js";

export const getDataAct = async (req, res) => {
  const id = req.query.id;
  try {
    const data = await KoyaAktuator.findAll({
      where: {
        id_user: id,
      },
      limit: 1,
      order: [["id", "DESC"]],
    });
    res.json(data);
  } catch (error) {
    console.log(error);
  }
};
