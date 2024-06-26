/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:58:42 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/08 14:20:29 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_bg_sound(t_mlx *mlx)
{
	if (!BASS_Init(-1, 44100, 0, 0, NULL))
		terminate_program(mlx);
	mlx->sound_stream[BG_SOUND] = BASS_StreamCreateFile(
			FALSE, "src/bonus/sound/nyan_cat.mp3", 0, 0, BASS_MUSIC_LOOP);
	if (!mlx->sound_stream[0])
		terminate_program(mlx);
	BASS_ChannelSetAttribute(mlx->sound_stream[BG_SOUND],
		BASS_ATTRIB_VOL, 0.01);
	mlx->cur_audio = 1;
	BASS_ChannelPlay(mlx->sound_stream[BG_SOUND], FALSE);
}

void	load_sound(t_mlx *mlx)
{
	mlx->sound_stream[DRINK_SOUND] = BASS_StreamCreateFile(
			FALSE, "src/bonus/sound/drink.mp3", 0, 0, 0);
	BASS_ChannelSetAttribute(mlx->sound_stream[DRINK_SOUND],
		BASS_ATTRIB_VOL, 1.0);
	mlx->sound_stream[OPEN_AND_DRINK_SOUND] = BASS_StreamCreateFile(
			FALSE, "src/bonus/sound/open_and_drink.mp3", 0, 0, 0);
	BASS_ChannelSetAttribute(mlx->sound_stream[OPEN_AND_DRINK_SOUND],
		BASS_ATTRIB_VOL, 1.0);
	mlx->sound_stream[WALK_SOUND] = BASS_StreamCreateFile(
			FALSE, "src/bonus/sound/walk.mp3", 0, 0, BASS_MUSIC_LOOP);
	BASS_ChannelSetAttribute(mlx->sound_stream[WALK_SOUND],
		BASS_ATTRIB_VOL, 1.0);
	mlx->sound_stream[RUN_SOUND] = BASS_StreamCreateFile(
			FALSE, "src/bonus/sound/run.mp3", 0, 0, BASS_MUSIC_LOOP);
	BASS_ChannelSetAttribute(mlx->sound_stream[RUN_SOUND],
		BASS_ATTRIB_VOL, 1.0);
}

void	play_sound(t_mlx *mlx, int audio_num)
{
	BASS_ChannelStop(mlx->sound_stream[mlx->cur_audio]);
	mlx->cur_audio = audio_num;
	BASS_ChannelSetPosition(mlx->sound_stream[audio_num], 0, BASS_POS_BYTE);
	BASS_ChannelPlay(mlx->sound_stream[audio_num], false);
}
