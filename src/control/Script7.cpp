#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "CarCtrl.h"
#include "ColStore.h"
#include "Coronas.h"
#include "CutsceneMgr.h"
#include "DMAudio.h"
#include "Explosion.h"
#include "GameLogic.h"
#include "General.h"
#include "Glass.h"
#include "Fluff.h"
#include "KeyGen.h"
#include "Hud.h"
#include "MBlur.h"
#include "Pad.h"
#include "Pickups.h"
#include "Pools.h"
#include "Population.h"
#include "Radar.h"
#include "RoadBlocks.h"
#include "Ropes.h"
#include "SetPieces.h"
#include "SpecialFX.h"
#include "Stats.h"
#include "Streaming.h"
#include "Timecycle.h"
#include "User.h"
#include "World.h"
#include "Zones.h"

// LCS: file done except TODOs

int8 CRunningScript::ProcessCommands1200To1299(int32 command)
{
	switch (command) {
	case todo__comm_1200:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1200");
		return 0;
	}
	case todo__comm_1201:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1201");
		return 0;
	}
	case todo__comm_1202:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1202");
		return 0;
	}
	case todo__comm_1203:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1203");
		return 0;
	}
	case todo__comm_1204:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1204");
		return 0;
	}
	case todo__comm_1205:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1205");
		return 0;
	}
	case todo__comm_1206:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1206");
		return 0;
	}
	case todo__comm_1207:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1207");
		return 0;
	}
	case todo__comm_1208:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1208");
		return 0;
	}
	case todo__comm_1209:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1209");
		return 0;
	}
	case todo__comm_1210:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1210");
		return 0;
	}
	case todo__comm_1211:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1211");
		return 0;
	}
	case todo__comm_1212:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1212");
		return 0;
	}
	case todo__comm_1213:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1213");
		return 0;
	}
	case todo__comm_1214:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1214");
		return 0;
	}
	case todo__comm_1215:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1215");
		return 0;
	}
	case todo__comm_1216:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1216");
		return 0;
	}
	case todo__comm_1217:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1217");
		return 0;
	}
	case todo__comm_1218:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1218");
		return 0;
	}
	case todo__comm_1219:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1219");
		return 0;
	}
	case todo__comm_1220:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1220");
		return 0;
	}
	case todo__comm_1221:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1221");
		return 0;
	}
	case todo__comm_1222:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1222");
		return 0;
	}
	case todo__comm_1223:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1223");
		return 0;
	}
	case todo__comm_1224:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1224");
		return 0;
	}
	case todo__comm_1225:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1225");
		return 0;
	}
	case todo__comm_1226:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1226");
		return 0;
	}
	case todo__comm_1227:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1227");
		return 0;
	}
	case todo__comm_1228:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1228");
		return 0;
	}
	case todo__comm_1229:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1229");
		return 0;
	}
	case todo__comm_1230:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1230");
		return 0;
	}
	case todo__comm_1231:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1231");
		return 0;
	}
	case todo__comm_1232:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1232");
		return 0;
	}
	case todo__comm_1233:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1233");
		return 0;
	}
	case todo__comm_1234:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1234");
		return 0;
	}
	case todo__comm_1235:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1235");
		return 0;
	}
	case todo__comm_1236:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1236");
		return 0;
	}
	case todo__comm_1237:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1237");
		return 0;
	}
	case todo__comm_1238:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1238");
		return 0;
	}
	case todo__comm_1239:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1239");
		return 0;
	}
	case todo__comm_1240:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1240");
		return 0;
	}
	case todo__comm_1241:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1241");
		return 0;
	}
	case todo__comm_1242:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1242");
		return 0;
	}
	case todo__comm_1243:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1243");
		return 0;
	}
	case todo__comm_1244:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1244");
		return 0;
	}
	case todo__comm_1245:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1245");
		return 0;
	}
	case todo__comm_1246:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1246");
		return 0;
	}
	case todo__comm_1247:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1247");
		return 0;
	}
	case todo__comm_1248:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1248");
		return 0;
	}
	case todo__comm_1249:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1249");
		return 0;
	}
	case todo__comm_1250:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1250");
		return 0;
	}
	case todo__comm_1251:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1251");
		return 0;
	}
	case todo__comm_1252:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1252");
		return 0;
	}
	case todo__comm_1253:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1253");
		return 0;
	}
	case todo__comm_1254:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1254");
		return 0;
	}
	case todo__comm_1255:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1255");
		return 0;
	}
	case todo__comm_1256:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1256");
		return 0;
	}
	case todo__comm_1257:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1257");
		return 0;
	}
	case todo__comm_1258:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1258");
		return 0;
	}
	case todo__comm_1259:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1259");
		return 0;
	}
	case todo__comm_1260:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1260");
		return 0;
	}
	case todo__comm_1261:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1261");
		return 0;
	}
	case todo__comm_1262:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1262");
		return 0;
	}
	case todo__comm_1263:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1263");
		return 0;
	}
	case todo__comm_1264:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1264");
		return 0;
	}
	case todo__comm_1265:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1265");
		return 0;
	}
	case todo__comm_1266:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1266");
		return 0;
	}
	case todo__comm_1267:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1267");
		return 0;
	}
	case todo__comm_1268:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1268");
		return 0;
	}
	case todo__comm_1269:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1269");
		return 0;
	}
	case todo__comm_1270:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1270");
		return 0;
	}
	case todo__comm_1271:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1271");
		return 0;
	}
	case todo__comm_1272:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1272");
		return 0;
	}
	case todo__comm_1273:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1273");
		return 0;
	}
	case todo__comm_1274:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1274");
		return 0;
	}
	case todo__comm_1275:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1275");
		return 0;
	}
	case todo__comm_1276:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1276");
		return 0;
	}
	case todo__comm_1277:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1277");
		return 0;
	}
	case todo__comm_1278:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1278");
		return 0;
	}
	case todo__comm_1279:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1279");
		return 0;
	}
	case todo__comm_1280:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1280");
		return 0;
	}
	case todo__comm_1281:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1281");
		return 0;
	}
	case todo__comm_1282:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1282");
		return 0;
	}
	case todo__comm_1283:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1283");
		return 0;
	}
	case todo__comm_1284:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1284");
		return 0;
	}
	case todo__comm_1285:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1285");
		return 0;
	}
	case todo__comm_1286:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1286");
		return 0;
	}
	case todo__comm_1287:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1287");
		return 0;
	}
	case todo__comm_1288:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1288");
		return 0;
	}
	case todo__comm_1289:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1289");
		return 0;
	}
	case todo__comm_1290:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1290");
		return 0;
	}
	case todo__comm_1291:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1291");
		return 0;
	}
	case todo__comm_1292:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1292");
		return 0;
	}
	case todo__comm_1293:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1293");
		return 0;
	}
	case todo__comm_1294:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1294");
		return 0;
	}
	case todo__comm_1295:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1295");
		return 0;
	}
	case todo__comm_1296:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1296");
		return 0;
	}
	case todo__comm_1297:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1297");
		return 0;
	}
	case todo__comm_1298:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1298");
		return 0;
	}
	case todo__comm_1299:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1299");
		return 0;
	}

	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands1300To1399(int32 command)
{
	switch (command) {
	case todo__comm_1300:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1300");
		return 0;
	}
	case todo__comm_1301:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1301");
		return 0;
	}
	case todo__comm_1302:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1302");
		return 0;
	}
	case todo__comm_1303:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1303");
		return 0;
	}
	case todo__comm_1304:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1304");
		return 0;
	}
	case todo__comm_1305:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1305");
		return 0;
	}
	case todo__comm_1306:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1306");
		return 0;
	}
	case todo__comm_1307:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1307");
		return 0;
	}
	case todo__comm_1308:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1308");
		return 0;
	}
	case todo__comm_1309:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1309");
		return 0;
	}
	case todo__comm_1310:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1310");
		return 0;
	}
	case todo__comm_1311:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1311");
		return 0;
	}
	case todo__comm_1312:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1312");
		return 0;
	}
	case todo__comm_1313:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1313");
		return 0;
	}
	case todo__comm_1314:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1314");
		return 0;
	}
	case todo__comm_1315:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1315");
		return 0;
	}
	case todo__comm_1316:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1316");
		return 0;
	}
	case todo__comm_1317:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1317");
		return 0;
	}
	case todo__comm_1318:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1318");
		return 0;
	}
	case todo__comm_1319:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1319");
		return 0;
	}
	case todo__comm_1320:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1320");
		return 0;
	}
	case todo__comm_1321:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1321");
		return 0;
	}
	case todo__comm_1322:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1322");
		return 0;
	}
	case todo__comm_1323:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1323");
		return 0;
	}
	case todo__comm_1324:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1324");
		return 0;
	}
	case todo__comm_1325:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1325");
		return 0;
	}
	case todo__comm_1326:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1326");
		return 0;
	}
	case todo__comm_1327:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1327");
		return 0;
	}
	case todo__comm_1328:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1328");
		return 0;
	}
	case todo__comm_1329:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1329");
		return 0;
	}
	case todo__comm_1330:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1330");
		return 0;
	}
	case todo__comm_1331:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1331");
		return 0;
	}
	case todo__comm_1332:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1332");
		return 0;
	}
	case todo__comm_1333:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1333");
		return 0;
	}
	case todo__comm_1334:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1334");
		return 0;
	}
	case todo__comm_1335:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1335");
		return 0;
	}
	case todo__comm_1336:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1336");
		return 0;
	}
	case todo__comm_1337:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1337");
		return 0;
	}
	case todo__comm_1338:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1338");
		return 0;
	}
	case todo__comm_1339:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1339");
		return 0;
	}
	case todo__comm_1340:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1340");
		return 0;
	}
	case todo__comm_1341:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1341");
		return 0;
	}
	case todo__comm_1342:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1342");
		return 0;
	}
	case todo__comm_1343:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1343");
		return 0;
	}
	case todo__comm_1344:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1344");
		return 0;
	}
	case todo__comm_1345:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1345");
		return 0;
	}
	case todo__comm_1346:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1346");
		return 0;
	}
	case todo__comm_1347:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1347");
		return 0;
	}
	case todo__comm_1348:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1348");
		return 0;
	}
	case todo__comm_1349:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1349");
		return 0;
	}
	case todo__comm_1350:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1350");
		return 0;
	}
	case todo__comm_1351:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1351");
		return 0;
	}
	case todo__comm_1352:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1352");
		return 0;
	}
	case todo__comm_1353:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1353");
		return 0;
	}
	case todo__comm_1354:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1354");
		return 0;
	}
	case todo__comm_1355:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1355");
		return 0;
	}
	case todo__comm_1356:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1356");
		return 0;
	}
	case todo__comm_1357:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1357");
		return 0;
	}
	case todo__comm_1358:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1358");
		return 0;
	}
	case todo__comm_1359:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1359");
		return 0;
	}
	case todo__comm_1360:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1360");
		return 0;
	}
	case todo__comm_1361:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1361");
		return 0;
	}
	case todo__comm_1362:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1362");
		return 0;
	}
	case todo__comm_1363:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1363");
		return 0;
	}
	case todo__comm_1364:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1364");
		return 0;
	}
	case todo__comm_1365:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1365");
		return 0;
	}
	case todo__comm_1366:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1366");
		return 0;
	}
	case todo__comm_1367:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1367");
		return 0;
	}
	case todo__comm_1368:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1368");
		return 0;
	}
	case todo__comm_1369:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1369");
		return 0;
	}
	case todo__comm_1370:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1370");
		return 0;
	}
	case todo__comm_1371:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1371");
		return 0;
	}
	case todo__comm_1372:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1372");
		return 0;
	}
	case todo__comm_1373:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1373");
		return 0;
	}
	case todo__comm_1374:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1374");
		return 0;
	}
	case todo__comm_1375:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1375");
		return 0;
	}
	case todo__comm_1376:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1376");
		return 0;
	}
	case todo__comm_1377:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1377");
		return 0;
	}
	case todo__comm_1378:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1378");
		return 0;
	}
	case todo__comm_1379:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1379");
		return 0;
	}
	case todo__comm_1380:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1380");
		return 0;
	}

	default:
		script_assert(0);
	}
	return -1;
}
