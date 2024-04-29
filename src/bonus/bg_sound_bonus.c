/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_sound_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:58:42 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/29 16:30:30 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_bg_sound(t_mlx *mlx)
{
	if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
		printf("BASS 초기화 실패: %d\n", BASS_ErrorGetCode());
		// return -1;
	}
	mlx->sound_stream = BASS_StreamCreateFile(FALSE, "src/bonus/original.mp3", 0, 0, BASS_MUSIC_LOOP);
	if (!mlx->sound_stream) {
		printf("파일 로드 실패: %d\n", BASS_ErrorGetCode());
		BASS_Free();
		// return -1;
	}
	BASS_ChannelSetAttribute(mlx->sound_stream, BASS_ATTRIB_VOL, 0.2);
	BASS_ChannelPlay(mlx->sound_stream, FALSE);
	// while (BASS_ChannelIsActive(streamHandle) == BASS_ACTIVE_PLAYING) {
	// 	// 이 부분에 적절한 sleep 함수를 사용해 CPU 사용률을 관리할 수 있습니다.
	// 	sleep(100);
	// }

}