var SM64Object = mem.typedef({
	graph_node_type:          u16,
	graph_flags:              u16,
	prev:                     u32,
	next:                     u32,
	graph_parent:             u32,
	graph_child:              u32,
	geo_layout_ptr:           u32,
	_18:                      u32,
	_1c:                      u32,
	_20:                      float,
	_24:                      float,
	_28:                      float,
	x_scaling:                float,
	y_scaling:                float,
	z_scaling:                float,
	_38:                      u16,
	_3a:                      u16,
	animation:                u32,
	anim_current_frame:       u16,
	anim_timer:               u16,
	anim_current_frame_copy:  u16,
	_46:                      u16,
	_48:                      u32,
	_4c:                      u32,
	matrix_ptr:               u32,
	float_54:                 u32,
	float_58:                 float,
	float_5c:                 float,
	next_object_ptr:          u32,
	_64:                      u32,
	next_object_ptr2:         u32,
	_6c:                      u32,
	_70:                      u32,
	active:                   u16,
	_76:                      u16,
	collided_obj_ptr:         u32,
	_7c:                      u32,
	_80:                      u32,
	_84:                      u32,
	_88:                      u32,
	obj_flags:                u32,
	_90:                      u32,
	_94:                      u32,
	_98:                      u32,
	_9c:                      u32,
	x_pos:                    float,
	y_pos:                    float,
	z_pos:                    float,
	x_speed:                  float,
	y_speed:                  float,
	z_speed:                  float,
	speed:                    float,
	_bc:                      u32,
	_c0:                      u32,
	x_rotation:               u32,
	y_rotation:               u32,
	z_rotation:               u32,
	x_rotation2:              u32,
	y_rotation2:              u32,
	z_rotation2:              u32,
	_dc:                      u32,
	_e0:                      u32,
	_e4:                      float,
	_e8:                      u32,
	_ec:                      u32,
	_f0:                      u32,
	_f4:                      u32,
	_f8:                      u32,
	_fc:                      u32,
	_100:                     u32,
	_104:                     u32,
	_108:                     u32,
	_10c:                     u32,
	_110:                     u32,
	_114:                     u32,
	_118:                     u32,
	_11c:                     u32,
	animation_ptr:            u32,
	_124:                     u32,
	_128:                     float,
	_12c:                     float,
	interaction:              u32,
	_134:                     u32,
	_138:                     u32,
	_13c:                     u32,
	_140:                     u32,
	behav_param:              u32,
	_148:                     u32,
	action:                   u32,
	_150:                     u32,
	timer:                    u32,
	_158:                     float,
	distance_from_mario:      float,
	_160:                     u32,
	_164_x:                   float,
	_168_y:                   float,
	_16c_z:                   float,
	_170:                     float,
	_174:                     float,
	_178:                     u32,
	transparency:             u32,
	damage_to_mario:          u32,
	health:                   u32,
	behav_param2:             u32,
	previous_action:          u32,
	_190:                     u32,
	collision_distance:       float,
	_198:                     u32,
	drawing_distance:         float,
	_1a0:                     u32,
	_1a4:                     u32,
	_1a8:                     u32,
	_1ac:                     u32,
	_1b0:                     u32,
	_1b4:                     u32,
	_1b8:                     u32,
	_1bc:                     u32,
	_1c0:                     u32,
	_1c4:                     u32,
	_1c8:                     u32,
	script_ptr:               u32,
	stack_index:              u32,
	stack:                    u32,
	_1d8:                     u32,
	_1dc:                     u32,
	_1e0:                     u32,
	_1e4:                     u32,
	_1e8:                     u32,
	_1ec:                     u32,
	_1f0:                     u32,
	_1f4:                     u16,
	_1f6:                     u16,
	col_sphere_x:             float,
	col_sphere_y:             float,
	_200:                     float,
	_204:                     float,
	_208:                     float,
	behavior_script:          u32,
	_210:                     u32,
	collide_obj_ptr:          u32,
	collision_ptr:            u32,
	_21c:                     u32,
	_220:                     u32,
	_224:                     u32,
	_228:                     u32,
	_22c:                     u32,
	_230:                     u32,
	_234:                     u32,
	_238:                     u32,
	_23c:                     u32,
	_240:                     u32,
	_244:                     u32,
	_248:                     u32,
	_24c:                     u32,
	_250:                     u32,
	_254:                     u32,
	_258:                     u32,
	behav_param_copy_ptr:     u32
});


SM64Object.prototype = {
	explode: function(){
		this.behavior_script = 0x13003510;
	}
}

var objects = [];

for(var i = 0; i < 240; i++)
{
	objects.push(new SM64Object(0x8033D488 + i * 0x260));
}

/*

// proc_levelscript_00
events.onexec(0x8037E2C4, function() {
	alert(objects[0]._04.hex(8));
})
*/

mem.bindvars(this, [
	[0x8033B21C, 'keys',  u8],
	[0x8033B21D, 'lives', u8],
	[0x8033B21E, 'power', u8],
	[0x8033B21D, 'subpower', u8],
]);