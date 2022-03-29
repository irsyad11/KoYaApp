import Koya from "../models/KoyaModel.js";

export const getData = async (req, res) => {
  const id = req.query.id;
  try {
    const data = await Koya.findAll({
      where: {
        id_user: id,
      },
      // limit: 1,
      order: [["id", "DESC"]],
    });
    res.json(data);
  } catch (error) {
    console.log(error);
  }
};
