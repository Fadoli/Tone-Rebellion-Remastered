# Coordinate destination orders

## Linked record fields and limits

The linked record is resolved from the selected island record's owner and
`+0x18` slot; it is not the `0x60`-stride island record itself. The relationship
to the tick records is now partly established: `FUN_0045c470` adds the tick
index to the linked record's member list and stores the linked-record index at
tick `+0x0c`. `FUN_004207f2` resolves that index back to the 100-byte record.
The tick loop still walks separate `0x4c`-byte records; these are linked by an
index, not pointer aliases. `FUN_0042219e` is the missing bridge: it resolves
the linked 100-byte record through `FUN_004207f2`, then, when the source
movement fields differ and the active tick task is not `FA_Cast`, copies linked
`+0x2c/+0x28/+0x30/+0x32` into tick `+0x3c/+0x40/+0x42/+0x44` and resets
progress `+0x46`. `FUN_004211bb` consumes task action 9 by entering movement
state 9 and copying the packed target to state target `+0x32`. The remake now
retains the linked-record order fields in `GameFloaterStart`, transfers them
while idle or on the source's 10-tick reevaluation cadence while moving, and
expands the packed coordinate through the existing movement kernel. `FA_Cast`
suppression and the action-9 follow-up candidate/site phases remain unported.
Evidence: re-evaluation
`ev_83d2c58354af7da0f0eac81274ce4acc13b27060e77eb7d82b4ed0f74897a266`,
task consumption `ev_9cf6e091e5052554584128e5f6d9e26420d03c257fa83061e471eda1b608d689`,
and per-tick call site `ev_838b98af4b5e94befce77b8cfdb9bdf9236d7b06d07b2827e533bd229c201f60`.
Evidence: click `ev_240065edaee45f4bdf20ff82a1512927f78528e1582d520091ea959f11b0553c`,
coordinate packing `ev_3bf0ee7cf769af3d7f196ff7feba294b3f489beddddf1f1dd24044ebc2b66397`,
packet handler `ev_ed75141a79f1bac30a4ad39dcad68e710e351330bcd3044aa3cb304ef2a796b2`,
receiver `ev_ca5765ec33347bfca0991a3af5bd70ed8b19b2861f9c7602494131d2f2a11ac3`,
link resolver `ev_b003c4e2130a4f653012f553ad5cdf8222b961d4c5b48c785fd40fdd3404ada2`,
and setters `ev_9e9d75f4978b9d45cbc2470a3ad2dd1de8e791f4494b0b8b090b15549e3f388e`,
`ev_b0d6dc330f48ea769d27f91e3813699594fed3422d909182391884696797306c`.
The overlapping consumer fields are in `ev_304a6608912493c1b44523c7772bcd6f09494423a083d84ab8d13bf71a9cadd9`;
the order resolver is `ev_3dacf152875bea4c5b8bb99e56b6957498377adcaad9c7f4859adaa76000677e`,
and the separate tick-array stride is visible in `ev_30ebdbae3fea9c425e667386d450d79579fcde7a1d8aee5d218f1a6ffd472942`.
The index/member-list bridge is visible in `FUN_0045c470` (`ev_c01195f2f3ed1ca7a62e0020adf82dd7c073012fa14e8f5f24ab95881aa1d886`),
its return-side update `FUN_0045c797` (`ev_12285d631e246f730c2af83500f82417af5296d9579ef2026df253a44e5ab8b4`),
and the tick resolver `FUN_004207f2` (`ev_4ba957496ff2a3530a78301b0817cddc1b012953d1cd526886b077c179347405`).
The follow-up probe found no allocating or copying behavior in
`FUN_0040fdab`/`FUN_0040fc15`; the former reads a stream value and the latter
delegates to a generic reader. `FUN_004393ab` uses that value as an index into
the 100-byte table but does not construct the records. A separate resolver
`FUN_0045c3bb` returns the floater record from the island runtime base, which
is distinct from `DAT_006192b0`. These observations still do not prove there
is no indirect bridge elsewhere. Evidence: readers
`ev_79dda344bee3d67d5436056ba79c453924e4f68fe5250e79ae4b33776f77ba56`,
`ev_eef27ecae291ea2f57b6c8af3658e9d80a4e46bf5db73dd5cb3baae9b9473158`,
100-byte index use `ev_9c544975a44a06a1d3cefc6f334b2b4b655d367acbd461fcd687ed6c77adc794`,
and floater resolver `ev_bd91d1af8a9010c3ecab74810610be6676463c93594d69f685adaebf0623a4ee`.
